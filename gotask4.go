package main

import (
	"fmt"
)

func main() {
	var number, firstPower, secondPower int
	fmt.Print("Введите число: ")
	fmt.Scan(&number)
	fmt.Print("Введите первую степень: ")
	fmt.Scan(&firstPower)
	fmt.Print("Введите вторую степень: ")
	fmt.Scan(&secondPower)

	resultFP := 1 // resultFP - результат возведения в первую степень
	for i := 1; i <= firstPower; i++ {
		resultFP = (resultFP * number) % 10 // возводим number в степень firstPower
	}

	resultSP := 1 // resultSP - результат возведения во вторую степень
	for i := 1; i <= secondPower; i++ {
		resultSP = (resultSP * resultFP) % 10 // возводим resultFP в степень secondPower
	}

	fmt.Println("Последняя цифра:", resultSP)
}
