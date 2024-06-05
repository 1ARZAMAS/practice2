// the generic Euclid algorithm + extended Euclid algorithm 
// 2nd task  + 3rd task

#include <iostream>
#include <vector>
using namespace std;

// Функция extendedEuclid находит НОД(a, b) и находит коэффициенты x и y в уравнении ax + by = НОД(a, b)
int extendedEuclid(int a, int b, int &x, int &y) {
  if (b == 0) { // Если b равно 0, то x равен 1, y равен 0 и возвращается a
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1;
  int d = extendedEuclid(b, a % b, x1, y1); // вызываем рекурсию с аргументами b и a % b
  // коэффициенты x1 и y1 вычисляются и обновляются новыми значениями x и y
  x = y1;
  y = x1 - (a / b) * y1;
  return d;
}

vector <int> euclid(int a, int b, int& x, int& y) {
    vector <int> A {a, 1, 0};
    vector <int> B {b, 0, 1};
    cout << A[0] << "\t" << A[1] << "\t" << A[2] << endl; //выводим текущие картежи
    cout << B[0] << "\t" << B[1] << "\t" << B[2] << endl;
    while (B[0] != 0) {
        int integer = A[0] / B[0]; //целая часть от деления чисел в картеже
        vector<int> remains {A[0] % B[0], A[1] - integer * B[1], A[2] - integer * B[2]};
        cout << remains[0] << "\t" << remains[1] << "\t" << remains[2] << "\t" << integer << endl;
        A = B;  //в первый картеж закидываем второй 
        B = remains;     //во второй закидываем с остатком
    }
    return A;
}


int main() {
    system("chcp 65001");
    int a, b;
    cout << "Введите два числа:"<< endl;
    cin >> a >> b;
    int x = 0, y = 0;
    vector <int> result = euclid(a, b, x, y);
    cout << "GCD:" << endl;
    cout << a << " * (" << result[1] << ") + " << b << " * (" << result[2] << ") = " << result[0] << endl;

    int m = 0;
    cout << "Введите модуль m: ";
    cin >> m;
    int da = extendedEuclid(a, m, x, y);
    // Если НОД(a, m) не равнен 1, то обратного элемента не существует
    if (da != 1) {
        cout << "Обратного элемента не существует" << endl;
    } else { // Иначе выводим x (взаимообратный элемент по модулю m)
        cout << "Взаимообратный элемент для числа a: " << (x % m + m) % m << endl;
    }

    int db = extendedEuclid(b, m, x, y);
    // Если НОД(b, m) не равнен 1, то обратного элемента не существует
    if (db != 1) {
        cout << "Обратного элемента не существует" << endl;
    } else { // Иначе выводим x (взаимообратный элемент по модулю m)
        cout << "Взаимообратный элемент для числа b: " << (x % m + m) % m << endl;
    }
    return 0;
}
