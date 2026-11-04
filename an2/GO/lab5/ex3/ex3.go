package main

import "fmt"

func main() {
	ch := make(chan string)

	go func() {
		ch <- "hello"
		ch <- "world"
	}()

	fmt.Println(<-ch)
	fmt.Println(<-ch)
}
