package main

import "fmt"

type Persoana struct {
	Nume   string
	Varsta int
}

func (p Persoana) Prezentare() string {
	return fmt.Sprintf("%s (%d de ani)", p.Nume, p.Varsta)
}

type Student struct {
	Persoana
	Grupa int
}

func (s Student) String() string {
	return fmt.Sprintf("%s, grupa %d", s.Prezentare(), s.Grupa)
}

func main() {
	s := Student{Persoana: Persoana{Nume: "Ana Popescu", Varsta: 21}, Grupa: 342}

	fmt.Println(s.String())
	fmt.Println(s.Prezentare())

}
