package main

import (
    "html/template"
    "log"
    "net/http"
    "time"
)

var dateChan chan string

func init() {
    dateChan = make(chan string, 10)
}

func main() {
    go makeMsg()

    http.HandleFunc("/", index)
    http.HandleFunc("/msg", printMsg)

    err := http.ListenAndServe("127.0.0.1:1335", nil)
    if err != nil {
        log.Fatal(err)
    }
}

func printMsg(w http.ResponseWriter, req *http.Request) {
    if req.Method != http.MethodPost {
        http.Error(
            w, "必须为POST请求", http.StatusMethodNotAllowed,
        )
        return
    }

    timeout := time.NewTimer(30 * time.Second)
    for {
        select {
        case <-timeout.C:
            w.WriteHeader(http.StatusOK)
            return
        case i := <-dateChan:
            _, err := w.Write([]byte(i))
            if err != nil {
                http.Error(
                    w, err.Error(), http.StatusInternalServerError,
                )
                return
            }
            return
        }
    }
}

func makeMsg() {
    ticker := time.NewTicker(3 * time.Second)
    for {
        select {
        case <-ticker.C:
            dateChan <- time.Now().Format("2006-01-02 15:04:05")
        }
    }
}

func index(w http.ResponseWriter, req *http.Request) {
    if req.Method != http.MethodGet {
        http.Error(
            w, "必须为GET请求", http.StatusMethodNotAllowed,
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
