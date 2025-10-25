#include <iostream>
#include <windows.h>   
using namespace std;

void arrayInfo(int* arr, int size) {
    cout << "Размер массива: " << size << endl;

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += *(arr + i); 
    }

    cout << "Сумма элементов: " << sum << endl;
    cout << "Первый элемент: " << *arr << endl;
    cout << "Последний элемент: " << *(arr + size - 1) << "\n\n";
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int numbers1[] = {1, 2, 3, 4, 5};
    int numbers2[] = {10, 20, 30, 40, 50, 60, 70};

    cout << "Информация о первом массиве:\n";
    arrayInfo(numbers1, 5);

    cout << "Информация о втором массиве:\n";
    arrayInfo(numbers2, 7);

    return 0;
}
