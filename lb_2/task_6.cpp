#include <iostream>
#include <windows.h>   
using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    const int N = 10;
    int a[N];   
    int b[N];  

    int* p = a;  //указываю на 1 элемент в массиве
    *p = 0;             
    *(p + 1) = 1;        
    for (int i = 2; i < N; i++) {
        int* cur = p + i;              
        *cur = *(cur - 1) + *(cur - 2);
    }

    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += *(p + i);
    }

    int* minPtr = p;  
    for (int i = 0; i < N; i++) {
        if (*(p + i) < *minPtr) {
            minPtr = p + i;
        }
    }

    int* q = b;                   
    for (int i = 0; i < N; i++) {
        *(q + i) = *(p + (N - 1 - i));
    }

    cout << "Массив Фибоначчи: ";
    for (int i = 0; i < N; i++) cout << *(p + i) << " ";
    cout << "\nСумма элементов: " << sum << endl;
    cout << "Минимальный элемент: " << *minPtr << endl;

    cout << "Массив 2 (обратная копия): ";
    for (int i = 0; i < N; i++) cout << *(q + i) << " ";
    cout << endl;

    return 0;
}
