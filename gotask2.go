package main

import (
	"fmt"
)

func extendedEuclid(a, b int) (int, int, int) {
	if b == 0 {
		return a, 1, 0
	}
	d, x1, y1 := extendedEuclid(b, a%b)
	x := y1
	y := x1 - (a/b)*y1
	return d, x, y
}

func euclid(a, b int) (int, int, int) {
	A := []int{a, 1, 0}
	B := []int{b, 0, 1}
	fmt.Printf("%d\t%d\t%d\n", A[0], A[1], A[2])
	fmt.Printf("%d\t%d\t%d\n", B[0], B[1], B[2])
	for B[0] != 0 {
		integer := A[0] / B[0]
		remains := []int{A[0] % B[0], A[1] - integer*B[1], A[2] - integer*B[2]}
		fmt.Printf("%d\t%d\t%d\t%d\n", remains[0], remains[1], remains[2], integer)
		A = B
		B = remains
	}
	return A[0], A[1], A[2]
}

func main() {
	var a, b int
	fmt.Println("Введите два числа:")
	fmt.Scan(&a, &b)

	gcd, x, y := euclid(a, b)
	fmt.Println("GCD:")
	fmt.Printf("%d * (%d) + %d * (%d) = %d\n", a, x, b, y, gcd)

	var m int
	fmt.Print("Введите модуль m: ")
	fmt.Scan(&m)

	da, xa, _ := extendedEuclid(a, m)
	if da != 1 {
		fmt.Println("Обратного элемента не существует")
	} else {
		fmt.Printf("Взаимообратный элемент для числа a: %d\n", (xa%m+m)%m)
	}

	db, xb, _ := extendedEuclid(b, m)
	if db != 1 {
		fmt.Println("Обратного элемента не существует")
	} else {
		fmt.Printf("Взаимообратный элемент для числа b: %d\n", (xb%m+m)%m)
	}
}
