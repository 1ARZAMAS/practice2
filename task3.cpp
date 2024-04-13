// 3rd task
// the extended Euclid algorithm 

#include <iostream>
using namespace std;

void extended_euclid(int num, int mod, int& firstRatio, int& secondRatio, int& result) {/* calculates a * *x + b * *y = gcd(a, b) = *d */
  long q, r, firstRatio1, firstRatio2, secondRatio1, secondRatio2;
  if (mod == 0) {
    mod = num; 
    firstRatio = 1; 
    secondRatio = 0;
    return;
  }

  firstRatio2 = 1, firstRatio1 = 0, secondRatio2 = 0, secondRatio1 = 1;

  while (mod > 0) {
    q = num / mod;
    r = num - q * mod;
    firstRatio = firstRatio2 - q * firstRatio1;
    secondRatio = secondRatio2 - q * secondRatio1;
    num = mod;
    mod = r;
    firstRatio2 = firstRatio1; 
    firstRatio1 = firstRatio; 
    secondRatio2 = secondRatio1; 
    secondRatio1 = secondRatio;
  }

  result = num; 
  firstRatio = firstRatio2; 
  secondRatio = secondRatio2;
}

int inverse(int num, int mod){/* computes the inverse of a modulo n */
  int result, firstRatio, secondRatio;

  extended_euclid(num, mod, firstRatio, secondRatio, result);
  if (result == 1) {
    return firstRatio;
  }
  return 0;
}

 int main(){
    int num = 7, mod = 11;
    cout << "Enter the number and the module " << endl;
    cin >> num >> mod;
    int reverse;
    int d = inverse(num, mod);
    cout << "Inverse number from " << num << " mod "<< mod  << " is " << d << endl;
    return 0;
}
