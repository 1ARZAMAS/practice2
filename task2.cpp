// the generic Euclid algorithm
// 2nd task 

#include <iostream>
#include <vector>
using namespace std;

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
    int a, b;
    cout << "Enter two numbers:"<< endl;
    cin >> a >> b;
    int x = 0, y = 0;
    vector <int> result = euclid(a, b, x, y);
    cout << "GCD:" << endl;
    cout << a << " * (" << result[1] << ") + " << b << " * (" << result[2] << ") = " << result[0] << endl;
    return 0;
}