#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    int year;
    bool isAvailable;

public:
    Book(string t, string a, string i, int y)
        : title(t), author(a), isbn(i), year(y), isAvailable(true) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    int getYear() const { return year; }
    bool getAvailability() const { return isAvailable; }

    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
    void setYear(int y) { year = y; }

    void borrow() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Книга \"" << title << "\" успешно выдана." << endl;
        } else {
            cout << "Книга \"" << title << "\" недоступна!" << endl;
        }
    }

    void returnBook() {
        if (!isAvailable) {
            isAvailable = true;
            cout << "Книга \"" << title << "\" возвращена в библиотеку." << endl;
        } else {
            cout << "Книга \"" << title << "\" уже находится в библиотеке." << endl;
        }
    }

    void displayInfo() const {
        cout << "Название: " << title
             << ", Автор: " << author
             << ", Год: " << year
             << ", ISBN: " << isbn
             << ", Статус: " << (isAvailable ? "Доступна" : "Выдана") << endl;
    }
};

class Library {
private:
    string name;
    string address;
    vector<Book> books;

public:
    Library(string n, string addr) : name(n), address(addr) {}

    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Книга добавлена: " << book.getTitle() << endl;
    }

    void removeBook(const string& isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == isbn) {
                cout << "Книга \"" << it->getTitle() << "\" удалена." << endl;
                books.erase(it);
                return;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
    }

    void findBook(const string& title) const {
        for (const auto& b : books) {
            if (b.getTitle() == title) {
                cout << "Найдена книга:" << endl;
                b.displayInfo();
                return;
            }
        }
        cout << "Книга \"" << title << "\" не найдена." << endl;
    }

    void borrowBook(const string& isbn) {
        for (auto& b : books) {
            if (b.getISBN() == isbn) {
                b.borrow();
                return;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
    }

    void returnBook(const string& isbn) {
        for (auto& b : books) {
            if (b.getISBN() == isbn) {
                b.returnBook();
                return;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
    }

    void displayAllBooks() const {
        cout << "\nВсе книги библиотеки \"" << name << "\" " << endl;
        for (const auto& b : books)
            b.displayInfo();
    }

    void displayAvailableBooks() const {
        cout << "\nДоступные книги" << endl;
        for (const auto& b : books)
            if (b.getAvailability())
                b.displayInfo();
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    Library lib("Центральная библиотека", "ул. Пушкина, 58");

    lib.addBook(Book("Война и мир", "Л. Толстой", "111-222", 1869));
    lib.addBook(Book("Преступление и наказание", "Ф. Достоевский", "333-444", 1866));
    lib.addBook(Book("Мастер и Маргарита", "М. Булгаков", "555-666", 1967));

    lib.displayAllBooks();

    lib.findBook("Мастер и Маргарита");

    lib.borrowBook("333-444");
    lib.borrowBook("333-444");  

    lib.returnBook("333-444");
    lib.returnBook("333-444");  

    lib.displayAvailableBooks();

    lib.removeBook("555-666");

    lib.displayAllBooks();

    return 0;
}
