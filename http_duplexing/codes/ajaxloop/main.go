package main

import (
    "html/template"
    "log"
    "net/http"
    "time"
)

func main() {
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

    _, err := w.Write([]byte(time.Now().Format("2006-01-02 15:04:05")))
    if err != nil {
        http.Error(
            w, err.Error(), http.StatusInternalServerError,
        )
    }
    return
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

    err = tpl.Execute(w, nil)
    if err != nil {
        http.Error(
            w, err.Error(), http.StatusInternalServerError,
        )
    }
    return
}
