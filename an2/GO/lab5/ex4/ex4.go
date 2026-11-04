package main

import "fmt"

func main() {
	ch := make(chan string)

	go func() {
		ch <- "hello"
		ch <- "world"
		ch <- "wowow"
		close(ch)
	}()

	msg := <-ch
	for msg != "" {
		fmt.Println(msg)
		msg = <-ch
	}
	fmt.Println("done")
}
