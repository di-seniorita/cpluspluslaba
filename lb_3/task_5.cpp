#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>

class Book {
    std::string title_, author_, isbn_;
    int year_{};
    bool available_{true};
public:
    Book(std::string t, std::string a, std::string i, int y)
        : title_(std::move(t)), author_(std::move(a)), isbn_(std::move(i)), year_(y) {}

    const std::string& title() const { return title_; }
    const std::string& author() const { return author_; }
    const std::string& isbn() const { return isbn_; }
    int year() const { return year_; }
    bool isAvailable() const { return available_; }

    bool borrow() {
        if (!available_) return false;
        available_ = false; return true;
    }
    void returnBook() { available_ = true; }

    void displayInfo() const {
        std::cout << "[" << isbn_ << "] " << title_ << " — " << author_
                  << " (" << year_ << ") " << (available_ ? "[Доступна]" : "[На руках]") << "\n";
    }
};

class Library {
    std::string name_, address_;
    std::vector<Book> books_;
public:
    Library(std::string n, std::string addr) : name_(std::move(n)), address_(std::move(addr)) {}

    void addBook(const Book& b) { books_.push_back(b); }

    bool removeBook(const std::string& isbn) {
        auto it = std::remove_if(books_.begin(), books_.end(), [&](const Book& b){ return b.isbn() == isbn; });
        if (it == books_.end()) return false;
        books_.erase(it, books_.end()); return true;
    }

    std::optional<Book> findBook(const std::string& title) const {
        for (const auto& b : books_) if (b.title() == title) return b;
        return std::nullopt;
    }

    bool borrowBook(const std::string& isbn) {
        for (auto& b : books_) if (b.isbn() == isbn) return b.borrow();
        return false;
    }

    bool returnBook(const std::string& isbn) {
        for (auto& b : books_) if (b.isbn() == isbn) { b.returnBook(); return true; }
        return false;
    }

    void displayAllBooks() const {
        std::cout << "Все книги (" << name_ << "):\n";
        for (const auto& b : books_) b.displayInfo();
    }

    void displayAvailableBooks() const {
        std::cout << "Доступные книги:\n";
        for (const auto& b : books_) if (b.isAvailable()) b.displayInfo();
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    Library lib("Городская библиотека", "ул. Центральная, 1");
    lib.addBook(Book("CLR via C#", "Jeffrey Richter", "978-5-8459-1555-2", 2013));
    lib.addBook(Book("Effective C++", "Scott Meyers", "978-0-321-33487-9", 2005));
    lib.addBook(Book("Clean Code", "Robert C. Martin", "978-0-13-235088-4", 2008));

    lib.displayAllBooks();
    std::cout << "\nБерем Clean Code\n";
    lib.borrowBook("978-0-13-235088-4");
    lib.displayAvailableBooks();
    std::cout << "\nВозврат Clean Code\n";
    lib.returnBook("978-0-13-235088-4");
    lib.displayAvailableBooks();
    return 0;
}
