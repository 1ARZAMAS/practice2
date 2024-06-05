#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

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

bool Prime(int a) {
    if (a == 1) { //единица - не простое число
        return false;
    }
    for (int i = 2; i < sqrt(a) + 1; i++) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
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

int modexp(int basis, int power, int modP) {
    if (power == 0) {
        return 1;
    }
    int z = modexp(basis % modP, power / 2, modP) % modP;
    if (power % 2 == 0) {
        return (z * z) % modP;
    }
    else {
        return ((basis % modP) * ((z * z) % modP)) % modP;
    }
}

pair<int, int> remainder(int& basis, int& power, int& modP) {
    pair<int, int> ost = { 1,1 };

    ost.first = modexp(basis, power, modP);

    int logByNumber = log2(power);     //рассматриваем остатки через логарифм и 2сс.
    vector<int> binary;  //переводим степень в 2сс.
    int power2 = power;
    while (power2 > 0) {
        binary.push_back(power2 % 2);
        power2 /= 2;
    }

    int resultForPrime = 1;
    for (int i = 0; i <= logByNumber; i++) {
        if (binary[i] == 1) { //бинарное не переворачиваем, а просто идем с "конца"
            int oneDegree = pow(2, i);
            resultForPrime *= modexp(basis, oneDegree, modP);
        }
    }
    ost.second = resultForPrime % modP;  //после смотрим на остаток

    return ost;  //вернем пару значений
}

int main() {
    system("chcp 65001");
    int basis = 0, power = 0, modP = 0;
    cout << "Введите основание числа: ";
    cin >> basis;
    cout << "Введите степень числа: ";
    cin >> power;
    cout << "Введите модуль числа: ";
    cin >> modP;
    bool zahod = false;

    if (basis < modP && power == (modP - 1) && (Prime(modP) == true)) { // Воспользуемся теоремой Ферма
        cout << "Согласно теореме Ферма получим: " << basis << "^" << power << " mod " << modP << " = 1" << endl;
        pair<int, int> ost = remainder(basis, power, modP);  //рассматриваем остатки через функцию
        cout << "Проверим, используя логарифм: " << ost.second << endl;
        zahod = true;
    }
    if (NOD(basis, modP) == 1 && power == EilerFunc(modP)) { // если числа взаимнопростые, можем воспользоваться теореой Эйлера
        zahod = true;
        cout << "Согласно теореме Эйлера получим: " << basis << "^" << power << " mod " << modP << " = 1" << endl;
        pair<int, int> ost = remainder(basis, power, modP);  //рассматриваем остатки через функцию
        cout << "Проверим, используя логарифм: " << ost.second << endl;
    }
    if (zahod == false) {
        power == EilerFunc(modP);
        int result = modexp(basis, power, modP);
        pair<int, int> ost = remainder(basis, power, modP);  //рассматриваем остатки через функцию
        cout << "Результат, используя свойства сравнений = " << ost.first << " и результат, используя логарифм = " << ost.second << endl;
    }

    int basis2 = 0, power2 = 0;
    cout << "Введите основание второго числа, которое будете сравнивать по модулю: ";
    cin >> basis2;
    cout << "Введите степень числа второго числа, которое будете сравнивать по модулю: ";
    cin >> power2;

    if (modexp(basis, power, modP) > modexp(basis2, power2, modP)){
        cout << basis << "^" << power << " mod " << modP << " > " << basis2 << "^" << power2 << " mod " << modP << endl;
    } else if (modexp(basis, power, modP) < modexp(basis2, power2, modP)){
        cout << basis << "^" << power << " mod " << modP << " < " << basis2 << "^" << power2 << " mod " << modP << endl;
    } else {
        cout << basis << "^" << power << " mod " << modP << " = " << basis2 << "^" << power2 << " mod " << modP << endl;
    }
    return 0;
}
