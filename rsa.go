package main

import (
	"crypto/rand"
	"fmt"
	"io/ioutil"
	"math/big"
	"os"
	"strings"
)

func isPrime(num int64) bool {
	if num <= 1 {
		return false
	}
	if num <= 3 {
		return true
	}
	if num%2 == 0 || num%3 == 0 {
		return false
	}
	for i := int64(5); i*i <= num; i += 6 {
		if num%i == 0 || num%(i+2) == 0 {
			return false
		}
	}
	return true
}

func getRandomNumber(min, max int64) int64 {
	for {
		num, err := rand.Int(rand.Reader, big.NewInt(max-min+1))
		if err != nil {
			panic(err)
		}
		num.Add(num, big.NewInt(min))
		if isPrime(num.Int64()) {
			return num.Int64()
		}
	}
}

func gcd(a, b int64) int64 {
	if b == 0 {
		return a
	}
	return gcd(b, a%b)
}

func eulerFunc(p int64) int64 {
	result := p
	for i := int64(2); i*i <= p; i++ {
		if p%i == 0 {
			for p%i == 0 {
				p /= i
			}
			result -= result / i
		}
	}
	if p > 1 {
		result -= result / p
	}
	return result
}

func extendedEuclid(a, b int64) (int64, int64, int64) {
	if b == 0 {
		return a, 1, 0
	}
	gcd, x1, y1 := extendedEuclid(b, a%b)
	x := y1
	y := x1 - (a/b)*y1
	return gcd, x, y
}

func modInverse(a, m int64) int64 {
	gcd, x, _ := extendedEuclid(a, m)
	if gcd != 1 {
		fmt.Println("Обратный элемент не существует, так как randE_open и phi_N не взаимно просты.")
		return -1
	}
	return (x%m + m) % m
}

func modPow(base, exp, mod int64) int64 {
	result := int64(1)
	for exp > 0 {
		if exp%2 == 1 {
			result = (result * base) % mod
		}
		base = (base * base) % mod
		exp /= 2
	}
	return result
}

func main() {
	min, max := int64(5000), int64(10000)
	randP, randQ := getRandomNumber(min, max), getRandomNumber(min, max)
	N := randP * randQ
	phiN := eulerFunc(N)
	randEOpen := getRandomNumber(min, phiN)
	for gcd(phiN, randEOpen) != 1 {
		randEOpen = getRandomNumber(min, phiN)
	}

	inversedDClosed := modInverse(randEOpen, phiN)

	opentext, err := ioutil.ReadFile("the picture of dorrian gray.txt")
	if err != nil {
		panic(err)
	}

	var encrypted []int64
	for _, c := range opentext {
		M := int64(c)
		if M > N {
			fmt.Println("Ошибка: символ вне допустимого диапазона для шифрования")
			continue
		}
		C := modPow(M, randEOpen, N)
		encrypted = append(encrypted, C)
	}

	ciphered, err := os.Create("cyphered_text.txt")
	if err != nil {
		panic(err)
	}
	defer ciphered.Close()

	for _, C := range encrypted {
		ciphered.WriteString(fmt.Sprintf("%d ", C))
	}

	fmt.Println("Шифрование завершено. Данные сохранены в 'cyphered_text.txt'.")

	cipheredtext, err := ioutil.ReadFile("cyphered_text.txt")
	if err != nil {
		panic(err)
	}

	var decrypted []byte
	nums := strings.Fields(string(cipheredtext))
	for _, numStr := range nums {
		if numStr != "" {
			num, success := new(big.Int).SetString(numStr, 10)
			if !success {
				fmt.Printf("Failed to parse number: %s\n", numStr)
				continue
			}
			M := modPow(num.Int64(), inversedDClosed, N)

			decrypted = append(decrypted, byte(M))
		}
	}

	decipheredtext, err := os.Create("decrypted_book.txt")
	if err != nil {
		panic(err)
	}
	defer decipheredtext.Close()

	_, err = decipheredtext.Write(decrypted)
	if err != nil {
		panic(err)
	}

	fmt.Println("Расшифровка завершена. Данные сохранены в 'decrypted_book.txt'.")
}
