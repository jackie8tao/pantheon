package main

import (
	"fmt"
	"html/template"
	"log"
	"net/http"
	"time"
)

var dateCh chan string

func init() {
	dateCh = make(chan string, 10)
}

func main() {
	go makeMsg()

	http.HandleFunc("/", index)
	http.HandleFunc("/msg", printMsg)

	err := http.ListenAndServe("127.0.0.1:1355", nil)
	if err != nil {
		log.Fatalln(err)
	}
}

func printMsg(w http.ResponseWriter, req *http.Request) {
	if req.Method != http.MethodGet {
		http.Error(
			w, "必须使用GET方法", http.StatusMethodNotAllowed,
		)
		return
	}

	timeout := time.NewTimer(30 * time.Second)
	for {
		select {
		case <-timeout.C:
			w.WriteHeader(http.StatusOK)
			_, err := w.Write([]byte(
				`<script type="text/javascript">parent.printMsg("结束");</script>`,
			))
			if err != nil {
				http.Error(
					w, err.Error(), http.StatusInternalServerError,
				)
			}
			return
		case i := <-dateCh:
			flusher, ok := w.(http.Flusher)
			if !ok {
				http.Error(
					w, "无法转换为flusher", http.StatusInternalServerError,
				)
				return
			}
			ret := fmt.Sprintf(
				`<script type="text/javascript">parent.printMsg("%s");</script>`,
				i,
			)
			_, err := w.Write([]byte(ret))
			if err != nil {
				http.Error(
					w, err.Error(), http.StatusInternalServerError,
				)
				return
			}
			flusher.Flush()
		}
	}
}

func makeMsg() {
	ticker := time.NewTicker(3 * time.Second)
	for {
		select {
		case <-ticker.C:
			dateCh <- time.Now().Format("2006-01-02 15:04:05")
		}
	}
}

func index(w http.ResponseWriter, req *http.Request) {
	if req.Method != http.MethodGet {
		http.Error(
			w, "必须使用GET方法", http.StatusMethodNotAllowed,
		)
		return
	}

	tpl, err := template.ParseFiles("index.html")
	if err != nil {
		http.Error(
			w, err.Error(), http.StatusInternalServerError,
		)
		return
	}

	if err = tpl.Execute(w, nil); err != nil {
		http.Error(
			w, err.Error(), http.StatusInternalServerError,
		)
		return
	}
}
