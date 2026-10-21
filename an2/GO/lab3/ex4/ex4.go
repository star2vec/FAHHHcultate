package main

import (
	"fmt"
	"strings"
)

func main() {
	var s string
	fmt.Scan(&s)

	s = strings.TrimSpace(s)
	s = strings.ToLower(s)

	n := len(s)
	sr := []rune(s)
	var i int
	var flag bool
	flag = true
	for i = 0; i < n/2; i++ {
		if sr[i] != sr[n-1-i] {
			flag = false
			break
		}
	}

	if flag == true {
		fmt.Print("palindrom")
	} else {
		fmt.Print("NU e palindrom")
	}

}
