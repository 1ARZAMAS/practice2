// 3rd task
// the extended Euclid algorithm 

#include <iostream>
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

int main() {
  system("chcp 65001");
  int a, m, x, y;
  cout << "Введите число a: ";
  cin >> a;
  cout << "Введите модуль m: ";
  cin >> m;

  int d = extendedEuclid(a, m, x, y);
  // Если НОД(a, m) не равнен 1, то обратного элемента не существует
  if (d != 1) {
    cout << "Обратного элемента не существует" << endl;
  } else { // Иначе выводим x (взаимообратный элемент по модулю m)
    cout << "Взаимообратный элемент: " << (x % m + m) % m << endl;
  }
  return 0;
}
