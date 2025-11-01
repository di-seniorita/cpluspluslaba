#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}
    virtual void display() const {
        cout << "Имя: " << name << ", Возраст: " << age << endl;
    }
};

class Employee {
protected:
    string position;
    double salary;

public:
    Employee(string pos, double sal) : position(pos), salary(sal) {}
    virtual void work() const {
        cout << "Выполняет работу как сотрудник" << endl;
    }
};

class Teacher : public virtual Person, public virtual Employee {
protected:
    string subject;
    int experienceYears;

public:
    Teacher(string n, int a, string pos, double sal, string subj, int exp)
        : Person(n, a), Employee(pos, sal), subject(subj), experienceYears(exp) {}

    void display() const override {
        cout << "Учитель: " << name << ", Возраст: " << age
             << ", Предмет: " << subject
             << ", Стаж: " << experienceYears << " лет"
             << ", Должность: " << position
             << ", Зарплата: " << salary << endl;
    }

    void work() const override {
        cout << "Преподаёт предмет: " << subject << endl;
    }

    void prepareLesson() const {
        cout << name << " готовит урок по предмету: " << subject << endl;
    }
};

class Researcher {
protected:
    string researchArea;
    int publicationsCount;

public:
    Researcher(string area, int publications)
        : researchArea(area), publicationsCount(publications) {}

    virtual void conductResearch() const {
        cout << "Проводит исследования в области: " << researchArea
             << " (" << publicationsCount << " публикаций)" << endl;
    }
};

class Professor : public Teacher, public Researcher {
private:
    string academicTitle;

public:
    Professor(string n, int a, string pos, double sal,
              string subj, int exp, string area, int pubs, string title)
        : Person(n, a),
          Employee(pos, sal),
          Teacher(n, a, pos, sal, subj, exp),
          Researcher(area, pubs),
          academicTitle(title) {}

    void display() const override {
        cout << "Профессор: " << name << ", Возраст: " << age
             << ", Звание: " << academicTitle
             << ", Должность: " << position
             << ", Зарплата: " << salary
             << ", Предмет: " << subject
             << ", Стаж преподавания: " << experienceYears << " лет"
             << ", Область исследований: " << researchArea
             << ", Публикаций: " << publicationsCount << endl;
    }

    void work() const override {
        cout << "Преподаёт " << subject << " и проводит научные исследования." << endl;
    }

    void superviseStudents() const {
        cout << name << " руководит дипломными проектами студентов." << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    cout << " Демонстрация класса учителя" << endl;
    Teacher t("Иван Петров", 35, "Преподаватель", 60000, "Математика", 10);
    t.display();
    t.work();
    t.prepareLesson();

    cout << "\n Демонстрация класса профессора" << endl;
    Professor p("Сергей Иванов", 50, "Профессор", 120000,
                "Физика", 25, "Квантовая механика", 45, "Доктор наук");
    p.display();
    p.work();
    p.conductResearch();
    p.superviseStudents();

    return 0;
}
