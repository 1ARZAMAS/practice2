
#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
bool isPrime(int num) { // проверка на простоту, откидываем сразу 1,2,3 и идем с шагом 6
    if (num <= 1) {
        return false;
    }
    if (num <= 3) {
        return true;
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int getRandomNumber(int min, int max) {  //генерация случайного числа в заданном диапазоне
    random_device rd; // получаем рандомное число исходя из характеристик компьютера
    mt19937 gen(rd()); // генерируем случайные числа
    uniform_int_distribution<> dist(min, max); // случайные числа в от min до max

    while (true) {
        int num = dist(gen);
        if (isPrime(num)) {
            return num;
        }
    }
}

int NOD(int firstNum, int secondNum) { // определяем наибольший общий делитель
    if (firstNum % secondNum == 0) {
        return secondNum;
    }
    if (secondNum % firstNum == 0) {
        return firstNum;
    }
    if (firstNum > secondNum) {
        return NOD(firstNum % secondNum, secondNum);
    }
    return NOD(firstNum, secondNum % firstNum);
}

int EilerFunc(int p) { // определяем количество взаимно простых чисел для p 
    int result = p;
    for (int i = 2; i * i <= p; i++) { //проходимся до корня из числа
        if (p % i == 0) { //если число разделилось на i, то мы уменьшаем р на i так как все числа,
            while (p % i == 0) { // которые делятся на i не являются взаимно простыми с p
                p /= i;
            }
            result -= result / i; // из результата вычитаем количество чисел result/i
        }
    }
    if (p > 1) { // если п - простое число, которое не разделилось, то оно простое и результатом
        result -= result / p; // функции будет р-1
    }

    return result;
}

int extendedEuclid(int firstNum, int secondNum, int &firstCoef, int &secondCoef) {
    if (secondNum == 0) {
        firstCoef = 1;
        secondCoef = 0;
        return firstNum;
    }

    int firstCoef1, secondCoef1;
    int gcd = extendedEuclid(secondNum, firstNum % secondNum, firstCoef1, secondCoef1);

    firstCoef = secondCoef1;
    secondCoef = firstCoef1 - (firstNum / secondNum) * secondCoef1;

    return gcd;
}

// Функция для нахождения мультипликативного обратного по модулю n
int modInverse(int randE_open, int phi_N) {
    int firstCoef, secondCoef;
    int gcd = extendedEuclid(randE_open, phi_N, firstCoef, secondCoef);

    if (gcd != 1) {
        cout << "Обратный элемент не существует, так как randE_open и phi_N не взаимно просты." << endl;
        return -1;
    } else {
        // Обеспечиваем, что x положителен
        return (firstCoef % phi_N + phi_N) % phi_N;
    }
}

long long modPower(long long base, long long exp, long long mod) { // возведение в степень по модулю
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}
