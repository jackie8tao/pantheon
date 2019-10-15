package main

import (
	"fmt"

	"github.com/casbin/casbin"
)

func main() {
	e := casbin.NewEnforcer("basic_model.conf", "basic_policy.csv")
	if e.Enforce("alice", "data1", "read") {
		fmt.Println("permit alice read data1")
		return
	}

	fmt.Println("deny alice read data1")
	return
}
