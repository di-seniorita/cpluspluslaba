#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;      
    int age;          
    double grades[5]; 
    double average;  

public:
    Student(const string& n, int a) {
        setName(n);
        setAge(a);
        for (int i = 0; i < 5; ++i)
            grades[i] = 0.0;
        average = 0.0;
    }

    void setName(const string& n) {
        if (!n.empty())
            name = n;
        else
            name = "Неизвестно";
    }

    string getName() const {
        return name;
    }

    void setAge(int a) {
        if (a >= 16 && a <= 100)
            age = a;
        else
            age = 18;
    }

    int getAge() const {
        return age;
    }

    void setGrade(int index, double grade) {
        if (index >= 0 && index < 5 && grade >= 2 && grade <= 5) {
            grades[index] = grade;
            calculateAverage(); 
        } else {
            cout << "Ошибка: некорректная оценка или индекс!" << endl;
        }
    }

    double getGrade(int index) const {
        if (index >= 0 && index < 5)
            return grades[index];
        else
            return -1; 
    }

    void calculateAverage() {
        double sum = 0.0;
        for (int i = 0; i < 5; ++i)
            sum += grades[i];
        average = sum / 5.0;
    }

    double getAverage() const {
        return average;
    }

    bool hasScholarship() const {
        return average >= 4.5;
    }

    void displayInfo() const {
        cout << "Имя: " << name << endl;
        cout << "Возраст: " << age << endl;
        cout << "Оценки: ";
        for (int i = 0; i < 5; ++i)
            cout << grades[i] << " ";
        cout << "\nСредний балл: " << average << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
   
    Student student("Иван Иванов", 20);

    student.setGrade(0, 5);
    student.setGrade(1, 4);
    student.setGrade(2, 5);
    student.setGrade(3, 3);
    student.setGrade(4, 4);

    student.displayInfo();

    if (student.hasScholarship()) {
        cout << "Студент получает стипендию" << endl;
    } else {
        cout << "Стипендия не назначена" << endl;
    }

    return 0;
}
