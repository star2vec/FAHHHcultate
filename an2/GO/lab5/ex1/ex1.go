package main

import "fmt"

func main() {
	var ch = make(chan string)

	go func() {
		ch <- "hello"
	}()
	fmt.Println(<-ch)
}
