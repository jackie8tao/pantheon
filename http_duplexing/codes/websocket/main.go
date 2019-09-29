package main

import (
    "github.com/gorilla/websocket"
    "html/template"
    "log"
    "net/http"
    "time"
)

var dateChan chan string
var wsUpgrader websocket.Upgrader

func init() {
    dateChan = make(chan string, 10)
    wsUpgrader = websocket.Upgrader{
        ReadBufferSize:  1024,
        WriteBufferSize: 1024,
    }
}

func main() {
    go makeMsg()

    http.HandleFunc("/", index)
    http.HandleFunc("/ws", printMsg)

    log.Fatal(http.ListenAndServe("127.0.0.1:1355", nil))
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

func printMsg(w http.ResponseWriter, req *http.Request) {
    conn, err := wsUpgrader.Upgrade(w, req, nil)
    if err != nil {
        http.Error(
            w, err.Error(), http.StatusInternalServerError,
        )
        return
    }

    defer conn.Close()

    for {
        select {
        case msg := <-dateChan:
            err := conn.WriteMessage(websocket.TextMessage, []byte(msg))
            if err != nil {
                log.Println("write:", err)
                return
            }
        }
    }
}

func index(w http.ResponseWriter, req *http.Request) {
    if req.Method != http.MethodGet {
        http.Error(
            w, "必须为GET方法", http.StatusMethodNotAllowed,
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
