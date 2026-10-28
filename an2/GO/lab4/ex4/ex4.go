package main

import (
	"fmt"
	"math"
)

type Cerc struct {
	raza float64
}

type Dreptunghi struct {
	latime   float64
	inaltime float64
}

type Triunghi struct {
	A float64
	B float64
	C float64
}

type Forma interface {
	Arie() float64
	Perimetru() float64
}

func (c Cerc) Arie() float64 {
	r := c.raza
	return math.Pi * r * r
}
func (d Dreptunghi) Arie() float64 {
	return d.latime * d.inaltime
}
func (t Triunghi) Arie() float64 {
	a := t.A
	b := t.B
	c := t.C
	p := (a + b + c) / 2
	return math.Sqrt(p * (p - a) * (p - b) * (p - c))
}

func (c Cerc) Perimetru() float64 {
	r := c.raza
	return 2 * math.Pi * r
}
func (t Triunghi) Perimetru() float64 {
	a := t.A
	b := t.B
	c := t.C
	return a + b + c
}
func (d Dreptunghi) Perimetru() float64 {
	return 2 * (d.latime + d.inaltime)
}

func main() {
	forme := []Forma{Cerc{3.0}, Triunghi{1.0, 2.0, 3.0}, Dreptunghi{4.0, 5.0}}

	var i int
	var fmax Forma
	var valmax float64

	valmax = 0.0
	for i = 0; i < len(forme); i++ {
		forma := forme[i]
		fmt.Printf("arie: %.2f, perimetru: %.2f\n", forma.Arie(), forma.Perimetru())
		if forma.Arie() > valmax {
			fmax = forma
			valmax = forma.Arie()
		}
	}
	fmt.Printf("tip maxim: %T", fmax)
}
