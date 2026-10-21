package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)

	if n < 2 {
		fmt.Print("nu e prim")
	} else if n == 2 {
		fmt.Print("prim!!")
	} else {
		var d int
		var flag bool

		flag = false
		for d = 2; d*d < n; d++ {
			if n%d == 0 {
				flag = true
				break
			}
		}

		if flag == false {
			fmt.Print("prim!!")
		} else {
			fmt.Print("nu e prim")
		}
	}
}
