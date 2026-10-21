package main

import "fmt"

func main() {
	v := []float32{0, 1, 2, 3, 4, 5}
	var idx int

	fmt.Scan(&idx)

	w := append(v[:idx], v[(idx+1):]...)

	fmt.Print(w)
}
