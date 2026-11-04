package main

import (
	"fmt"
	"sync"
)

func main() {
	ch := make(chan string)
	wg := sync.WaitGroup{}

	wg.Add(1)
	go func() {
		defer wg.Done()
		msg := <-ch
		fmt.Println(msg)
	}()

	ch <- "hello"
	wg.Wait()
}
