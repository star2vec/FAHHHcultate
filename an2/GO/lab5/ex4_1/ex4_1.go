package main

import (
	"time"
)

func processing(ch chan bool) {
	time.Sleep(200 * time.Microsecond)
	ch <- true
}

func main() {
	ch := make(chan bool)
	<-ch
}
