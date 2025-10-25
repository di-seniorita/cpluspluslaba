#include <iostream>
#include <string>
#include <windows.h>
#include <limits>
using namespace std;

struct Book {
    string title;   
    string author; 
    int year;     
    double price; 
};

void printBooks(Book* books, int size) {
    cout << "\nСписок книг:\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ":"; cout << books[i].title <<"; ";
        cout << books[i].author <<"; ";
        cout << books[i].year <<" г.; ";
        cout << books[i].price << " руб.";
        cout << endl;
    }
}

void findExpensive(Book* books, int size) {
    if (size == 0) return;
    int index = 0; 
    for (int i = 1; i < size; i++) {
        if (books[i].price > books[index].price) {
            index = i;
        }
    }

    cout << "\nСамая дорогая книга:\n";
    cout << "  Название: " << books[index].title << endl;
    cout << "  Автор: " << books[index].author << endl;
    cout << "  Год издания: " << books[index].year << endl;
    cout << "  Цена: " << books[index].price << " руб.\n";
}

int main() {
    SetConsoleOutputCP(65001);  
    SetConsoleCP(65001);        
    setlocale(LC_ALL, "ru_RU.UTF-8"); 

    int N;
    cout << "Введите количество книг: ";
    cin >> N;

    if (N <= 0) {
        cout << "Неверное количество книг.\n";
        return 0;
    }

    Book* books = new Book[N];

    for (int i = 0; i < N; i++) {
        cout << "\nВведите данные для книги " << i + 1 << ":\n";
        cout << "Название: ";
        cin.ignore(); 
        getline(cin, books[i].title);
        cout << "Автор: ";
        getline(cin, books[i].author);
        cout << "Год издания: ";
        cin >> books[i].year;
        cout << "Цена: ";
        cin >> books[i].price;
    }

    printBooks(books, N);

    findExpensive(books, N);

    delete[] books;

    cout << "\nПамять освобождена. Программа завершена.\n";
    return 0;
}
