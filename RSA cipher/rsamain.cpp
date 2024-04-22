#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <sstream>

#include "header.h"
using namespace std;

ostream& operator << (ostream& os, const vector<long long>& ciphered){ //Перегрузка вывода
    for (auto const& M : ciphered) {
        os << M << " ";  // Преобразование чисел обратно в символы
    }
    return os;
}

istream& operator >> (istream& is, vector <long long>& opentext){ // Перегрузка ввода
    long long i;
    while (is >> i){
        opentext.push_back(i);
    }
    return is;
}

int main(){
    system("chcp 65001");
    int min = 5000, max = 10000;
    int randP = getRandomNumber(min, max), randQ = getRandomNumber(min, max); // генерируем случайные простые числа
    int N = randP * randQ;
    int phi_N = EilerFunc(N); // вычисляем ф(N) с помощью функции Эйлера
    int randE_open = getRandomNumber(min, phi_N); // генерируем случайное число, которое будет меньше ф(N)
    while (NOD(phi_N, randE_open) != 1){ 
        randE_open = getRandomNumber(min, phi_N); // если число не взаимно простое с ф(N), то создаем его заново
    }

    int inversedD_closed = modInverse(randE_open, phi_N);
    
    ifstream opentext("eugenii onegin.txt");
    vector<long long> encrypted;

    // Чтение и шифрование файла по одному символу
    char c;
    while (opentext.get(c)) {
        long long M = static_cast<long long>(c); // преобразовываем чар в лонг лонг
        if (M > N) {
            cout << "Ошибка: символ вне допустимого диапазона для шифрования" << endl;
            cout << "Шифрование прервано!" << endl;
            return -1;
        }
        long long C = modPower(M, randE_open, N); // возводим в степень по модулю
        encrypted.push_back(C); // и закидываем в вектор
    }
    opentext.close();

    // Сохранение зашифрованных данных в новый файл
    ofstream ciphered("cyphered_text.txt");
    ciphered << encrypted;
    ciphered.close();

    cout << "Шифрование завершено. Данные сохранены в 'cyphered_text.txt'." << endl;

    // Открытие зашифрованного файла
    ifstream cipheredtext("cyphered_text.txt");

    vector<long long> decrypted;

    cipheredtext >> decrypted;

    for (auto &symb : decrypted){
        symb =  modPower(symb, inversedD_closed, N);  // Расшифровка
    }

    cipheredtext.close();

    // Запись расшифрованного текста в новый файл
    ofstream decipheredtext("decrypted_book.txt");

    decipheredtext << string(decrypted.begin(), decrypted.end());
    decipheredtext.close();
    
    cout << "Расшифровка завершена. Данные сохранены в 'decrypted_book.txt'." << endl;
    return 0;
}
