#include <iostream>
using namespace std;

int main() {
    system("chcp 65001");
    int number, firstPower, secondPower;
    cout << "Введите число: ";
    cin >> number;
    cout << "Введите степень: ";
    cin >> firstPower;
    cout << "Введите 2 степень: ";
    cin >> secondPower;
    int resultFP = 1;                                    // resultFP - результат возведения в первую степень
    for (int i = 1; i <= firstPower; i++) {              // возводим number в степень firstPower
        resultFP = (resultFP * number) % 10;             // при каждом умножении на number берем последнюю цифру
    }
    int resultSP = 1;                                    // e - результат возведения во вторую степень
    for (int i = 1; i <= secondPower; i++) {             // возводим resultFP в степень secondPower
        resultSP = (resultSP * resultFP) % 10;           // при каждом умножении на resultFP берем последнюю цифру
    }
    cout << "Последняя цифра: "<< resultSP << endl;
    return 0;
}
