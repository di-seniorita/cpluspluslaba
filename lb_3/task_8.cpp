#include <iostream>
#include <string>

class Person {
protected:
    std::string name_;
    int age_;
public:
    Person(std::string n, int a) : name_(std::move(n)), age_(a) {}
    virtual ~Person() = default;
    virtual void display() const { std::cout << "Имя: " << name_ << ", Возраст: " << age_ << "\n"; }
};

class Employee {
protected:
    std::string position_;
    double salary_;
public:
    Employee(std::string pos, double sal) : position_(std::move(pos)), salary_(sal) {}
    virtual ~Employee() = default;
    virtual void work() const { std::cout << "Выполняет работу как сотрудник\n"; }
};

class Teacher : public Person, public Employee {
    std::string subject_;
    int years_;
public:
    Teacher(std::string n, int a, std::string pos, double sal, std::string subj, int yrs)
        : Person(std::move(n), a), Employee(std::move(pos), sal),
          subject_(std::move(subj)), years_(yrs) {}

    void display() const override {
        Person::display();
        std::cout << "Должность: " << position_ << ", Зарплата: " << salary_
                  << ", Предмет: " << subject_ << ", Стаж: " << years_ << "\n";
    }
    void work() const override { std::cout << "Преподает предмет: " << subject_ << "\n"; }
    void grade() const { std::cout << "Ставит оценки студентам\n"; }
};

class Researcher {
protected:
    std::string area_;
    int pubs_;
public:
    Researcher(std::string area, int publications) : area_(std::move(area)), pubs_(publications) {}
    void conductResearch() const { std::cout << "Исследования в области: " << area_ << ", публ.: " << pubs_ << "\n"; }
};

class Professor : public Teacher, public Researcher {
public:
    Professor(std::string n, int a, std::string pos, double sal, std::string subj, int yrs,
              std::string area, int pubs)
        : Teacher(std::move(n), a, std::move(pos), sal, std::move(subj), yrs),
          Researcher(std::move(area), pubs) {}

    void display() const override {
        Teacher::display();
        std::cout << "Профессор, научная область: " << area_ << ", публ.: " << pubs_ << "\n";
    }
    void work() const override {
        Teacher::work();
        std::cout << "Руководит исследованиями\n";
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Teacher t("Ирина", 35, "Преподаватель", 90000, "ОП", 10);
    t.display(); t.work(); t.grade();
    std::cout << "\n";
    Professor p("Сергей", 50, "Профессор", 150000, "ООП", 20, "ML", 120);
    p.display(); p.work(); p.conductResearch();
    return 0;
}
