#include <iostream>
#include <string>
#include <iomanip>

class Person {
protected:
    std::string name_;
    int age_;
    std::string address_;

public:
    Person(std::string n, int a, std::string addr)
        : name_(std::move(n)), age_(a), address_(std::move(addr)) {}
    virtual ~Person() = default;

    virtual void displayInfo() const {
        std::cout << "Имя: " << name_ << ", Возраст: " << age_ << ", Адрес: " << address_ << "\n";
    }
};

class Student : public Person {
private:
    std::string studentId_;
    double averageGrade_{};

public:
    Student(std::string n, int a, std::string addr, std::string sid, double avg)
        : Person(std::move(n), a, std::move(addr)), studentId_(std::move(sid)), averageGrade_(avg) {}

    void setAverageGrade(double g) {
        if (g < 0 || g > 5) throw std::out_of_range("Средний балл 0..5");
        averageGrade_ = g;
    }

    void displayInfo() const override {
        Person::displayInfo();
        std::cout << "ID: " << studentId_ << ", Средний балл: " << std::fixed << std::setprecision(2) << averageGrade_ << "\n";
    }
};

class Professor : public Person {
private:
    std::string department_;
    double salary_{};
    int yearsOfExp_{};

public:
    Professor(std::string n, int a, std::string addr, std::string dept, double sal, int y)
        : Person(std::move(n), a, std::move(addr)), department_(std::move(dept)), salary_(sal), yearsOfExp_(y) {}

    double calcSeniorityBonus() const {
        // простая модель: 1% от зарплаты за каждый год, максимум 30%
        double rate = std::min(30, yearsOfExp_) * 0.01;
        return salary_ * rate;
    }

    void displayInfo() const override {
        Person::displayInfo();
        std::cout << "Кафедра: " << department_
                  << ", Оклад: " << salary_
                  << ", Стаж: " << yearsOfExp_
                  << ", Надбавка: " << calcSeniorityBonus() << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    Student student("Петр Петров", 20, "ул. Студенческая, 15", "S12345", 4.3);
    Professor prof("Доктор Иванов", 45, "ул. Академическая, 10", "Компьютерные науки", 50000, 15);

    student.displayInfo();
    prof.displayInfo();
    return 0;
}
