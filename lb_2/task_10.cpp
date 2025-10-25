#include <iostream>
#include <string>
#include <limits>
#include <windows.h>
using namespace std;

struct Book {
    string title;  
    string author;  
    int    year;    
    double price;  
};

void printBooks(Book* books, int size) {
    cout << "\nСписок книг:\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ") " << books[i].title << "; "
             << books[i].author << "; "
             << books[i].year   << " г.; "
             << books[i].price  << " руб.\n";
    }
}

void sortBooksByYear(Book* books, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (books[j].year > books[j + 1].year) {
                Book tmp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = tmp;
            }
        }
    }
}

Book* findBookByAuthor(Book* books, int size, const std::string& author) {
    for (int i = 0; i < size; i++) {
        if (books[i].author == author) {
            return &books[i];        
        }
    }
    return nullptr;            
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистить \n перед getline
        getline(cin, books[i].title);

        cout << "Автор: ";
        getline(cin, books[i].author);

        cout << "Год издания: ";
        cin >> books[i].year;

        cout << "Цена: ";
        cin >> books[i].price;
    }

    printBooks(books, N);

    sortBooksByYear(books, N);
    cout << "\nПосле сортировки по году (по возрастанию):";
    printBooks(books, N);

    cout << "\nВведите имя автора для поиска: ";
    cin.ignore(numeric_limits<streamsize>:: max(), '\n');
    string queryAuthor;
    getline(cin, queryAuthor);

    Book* found = findBookByAuthor(books, N, queryAuthor);
    if (found) {
        cout << "Найдена книга автора \"" << queryAuthor << "\":\n";
        cout << found->title << "; " << found->author << "; "
             << found->year << " г.; " << found->price << " руб.\n";
    } else {
        cout << "Книга автора \"" << queryAuthor << "\" не найдена.\n";
    }

    delete[] books;
    cout << "\nПамять освобождена. Программа завершена.\n";
    return 0;
}
