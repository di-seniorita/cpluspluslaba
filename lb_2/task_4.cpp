#include <iostream>
using namespace std;

void swapValues1(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    cout << "внутри функции по значению: a = " << a << ", b = " << b << endl;
}

void swapValues2(int* a, int* b) {
    int temp = *a;   
    *a = *b;
    *b = temp;
    cout << "внутри функции по указателю: *a = " << *a << ", *b = " << *b << endl;
}

void swapValues3(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
    cout << "внутри функции по ссылке: a = " << a << ", b = " << b << endl;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int x = 3, y = 7;

    cout << "Исходные значения: x = " << x << ", y = " << y << endl;

    swapValues1(x, y);
    cout << "После вызова swapValues1 (по значению): x = " << x << ", y = " << y << endl << endl;

    swapValues2(&x, &y);
    cout << "После вызова swapValues2 (по указателям): x = " << x << ", y = " << y << endl << endl;

    swapValues3(x, y);
    cout << "После вызова swapValues3 (по ссылке): x = " << x << ", y = " << y << endl;

    return 0;
}
