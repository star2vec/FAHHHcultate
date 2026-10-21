package main

import "fmt"

func main() {
	slice := []string{"Dezvoltarea", "aplicațiilor", "web"}

	var i int
	n := len(slice)
	for i = 0; i < n/2; i++ {
		aux := slice[i]
		slice[i] = slice[n-i-1]
		slice[n-1-i] = aux
	}

	fmt.Print(slice)

}
