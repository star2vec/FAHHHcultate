package main

import "fmt"

func interschimba(a, b *int) {
	*a, *b = *b, *a
}

func dubleaza(x *int) {
	*x = 2 * (*x)
}

func main() {
	var a int
	var b int

	a = 3
	b = 5
	fmt.Printf("%d %d\n", a, b)

	interschimba(&a, &b)
	fmt.Printf("%d %d\n", a, b)

	dubleaza(&b)
	fmt.Printf("%d %d\n", a, b)
}
