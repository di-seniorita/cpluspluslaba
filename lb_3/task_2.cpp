#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
    string address;

public:
    Person(string n, int a, string addr) : name(n), age(a), address(addr) {}
    virtual void displayInfo() const {
        cout << "Имя: " << name << ", Возраст: " << age << ", Адрес: " << address << endl;
    }
    virtual ~Person() {}
};

class Student : public Person {
private:
    string studentId;
    double averageGrade;

public:
    Student(string n, int a, string addr, string id, double grade)
        : Person(n, a, addr), studentId(id), averageGrade(grade) {}

    void displayInfo() const override {
        cout << "Студент: " << name
             << ", Возраст: " << age
             << ", Адрес: " << address
             << ", ID: " << studentId
             << ", Средний балл: " << averageGrade << endl;
    }

    void setAverageGrade(double grade) {
        averageGrade = grade;
    }

    double getAverageGrade() const {
        return averageGrade;
    }
};


class Professor : public Person {
private:
    string department;
    double salary;
    int yearsOfExperience;

public:
    Professor(string n, int a, string addr, string dept, double sal, int years)
        : Person(n, a, addr), department(dept), salary(sal), yearsOfExperience(years) {}

    void displayInfo() const override {
        cout << "Профессор: " << name
             << ", Возраст: " << age
             << ", Адрес: " << address
             << ", Кафедра: " << department
             << ", Зарплата: " << salary
             << ", Стаж: " << yearsOfExperience
             << " лет, Надбавка: " << calculateBonus() << endl;
    }

    double calculateBonus() const {
        return salary * 0.02 * yearsOfExperience; 
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


