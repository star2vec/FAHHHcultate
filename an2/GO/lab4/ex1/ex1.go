package main

import "fmt"

func statistici(numere []int) (int, int, float64) {
	var mini int
	var maxi int
	var suma int
	var medie float64
	var i int
	var x int

	suma = numere[0]
	mini = numere[0]
	maxi = numere[0]
	for i = 1; i < len(numere); i++ {
		x = numere[i]
		if x < mini {
			mini = x
		}
		if x > maxi {
			maxi = x
		}
		suma += x
	}

	medie = float64(suma) / float64(len(numere))
	return mini, maxi, medie
}

func main() {
	var mini int
	var maxi int
	var medie float64

	numere := []int{4, 8, 15, 16, 23, 42}

	mini, maxi, medie = statistici(numere)
	fmt.Printf("%d %d %.2f\n", mini, maxi, medie)

	mini, maxi, _ = statistici(numere)
	fmt.Printf("%d %d\n", mini, maxi)
}
