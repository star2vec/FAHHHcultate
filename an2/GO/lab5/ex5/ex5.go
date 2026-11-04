package main

import "fmt"

func send(ch chan<- string) {
	ch <- "hello :p"
}

func receive(ch <-chan string) string {
	return <-ch
}

func main() {
	ch := make(chan string)

	go send(ch)
	ch2 := receive(ch)
	fmt.Println(ch2)
}
