package main

import "fmt"

func main() {

	var info = map[string]int{
		"Andrei": 190,
		"Maria":  165,
		"Ion":    182,
		"Elena":  172,
		"George": 178,
		"Ana":    165,
	}

	nume := make([]string, 0, len(info))
	for elem := range info {
		nume = append(nume, elem)
	}

	var i int
	var j int
	n := len(info)
	for i = 0; i < n; i++ {
		for j = i + 1; j < n; j++ {
			if info[nume[i]] < info[nume[j]] {
				aux := nume[i]
				nume[i] = nume[j]
				nume[j] = aux
			}
		}
	}

	fmt.Print(nume)

}
