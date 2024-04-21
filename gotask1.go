package main

import (
	"fmt"
	"math"
)

func NOD(firstNum, secondNum int) int { // определение НОД
	if firstNum%secondNum == 0 {
		return secondNum
	}
	if secondNum%firstNum == 0 {
		return firstNum
	}
	if firstNum > secondNum {
		return NOD(firstNum%secondNum, secondNum)
	}
	return NOD(firstNum, secondNum%firstNum)
}

func Prime(a int) bool {
	if a == 1 {
		return false // 1 не простое число
	}
	for i := 2; i <= int(math.Sqrt(float64(a))); i++ {
		if a%i == 0 {
			return false
		}
	}
	return true
}

func EilerFunc(p int) int { // функция Эйлера
	result := p
	for i := 2; i*i <= p; i++ { // до корня из числа
		if p%i == 0 { // если число делится
			for p%i == 0 {
				p /= i
			}
			result -= result / i // уменьшаем результат на количество чисел result/i
		}
	}
	if p > 1 { // если число не делится, то оно простое
		result -= result / p
	}
	return result
}

func modexp(basis, power, modP int) int { // возведение в степень по модулю
	if power == 0 {
		return 1
	}
	z := modexp(basis%modP, power/2, modP) % modP
	if power%2 == 0 {
		return (z * z) % modP
	}
	return ((basis % modP) * ((z * z) % modP)) % modP
}

func remainder(basis, power, modP int) (int, int) {
	first := modexp(basis, power, modP)

	var binary []int
	power2 := power
	for power2 > 0 {
		binary = append(binary, power2%2)
		power2 /= 2
	}

	second := 1
	for i, val := range binary {
		if val == 1 {
			oneDegree := int(math.Pow(2, float64(i)))
			second *= modexp(basis, oneDegree, modP)
		}
	}
	return first, second % modP
}

func main() {
	var basis, power, modP int
	fmt.Println("Введите основание числа:")
	fmt.Scanf("%d", &basis)
	fmt.Scanln()
	fmt.Println("Введите степень числа:")
	fmt.Scanf("%d", &power)
	fmt.Scanln()
	fmt.Println("Введите модуль числа:")
	fmt.Scanf("%d", &modP)
	fmt.Scanln()

	var zahod bool

	if basis < modP && power == (modP-1) && Prime(modP) {
		fmt.Printf("Согласно теореме Ферма получим: %d^%d mod %d = 1\n", basis, power, modP)
		_, second := remainder(basis, power, modP)
		fmt.Printf("Проверим, используя логарифм: %d\n", second)
		zahod = true
	}

	if NOD(basis, modP) == 1 && power == EilerFunc(modP) && zahod == false {
		fmt.Printf("Согласно теореме Эйлера получим: %d^%d mod %d = 1\n", basis, power, modP)
		_, second := remainder(basis, power, modP)
		fmt.Printf("Проверим, используя логарифм: %d\n", second)
		zahod = true
	}

	if !zahod {
		power = EilerFunc(modP)
		first, second := remainder(basis, power, modP)
		fmt.Printf("Результат, используя свойства сравнений = %d, и результат, используя логарифм = %d\n", first, second)
	}

	var basis2, power2 int
	fmt.Println("Введите основание второго числа:")
	fmt.Scanf("%d", &basis2)
	fmt.Scanln()

	fmt.Println("Введите степень второго числа:")
	fmt.Scanf("%d", &power2)
	fmt.Scanln()

	first1 := modexp(basis, power, modP)
	first2 := modexp(basis2, power2, modP)

	if first1 > first2 {
		fmt.Printf("%d^%d mod %d > %d^%d mod %d\n", basis, power, modP, basis2, power2, modP)
	} else {
		fmt.Printf("%d^%d mod %d < %d^%d mod %d\n", basis, power, modP, basis2, power2, modP)
	}
}
