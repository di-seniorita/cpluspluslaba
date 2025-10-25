#include <iostream>
#include <string>
#include <windows.h>   
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    string fio;   
    Date birth;  
    int grades[5];
};

void printStudent(const Student& s) {
    cout << "ФИО: " << s.fio << "\n";
    cout << "Дата рождения: " << s.birth.day << "." << s.birth.month << "." << s.birth.year << "\n";
    cout << "Оценки: ";
    for (int i = 0; i < 5; i++) {
        cout << s.grades[i] << " ";
    }
    cout << "\n";
}

double getAverageRating(const Student& s) {
    int sum = 0;
    for (int i = 0; i < 5; i++) sum += s.grades[i];
    return static_cast<double>(sum) / 5.0;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    Student group[4] = {
        {"Ишмухаметова Диана Руслановна", {10, 2, 2003}, {5, 5, 5, 4, 5}},
        {"Калашникова Мария Олеговна", {1, 11, 2003}, {3, 4, 4, 3, 4}},
        {"Бегемотов Илья Сергеевич", {25, 7, 2004}, {5, 5, 5, 5, 4}},
        {"Стажкина Полина Сергеевна", {9, 1, 2005}, {4, 4, 4, 4, 4}}
    };

    cout << "Список студентов:\n\n";
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ") ";
        printStudent(group[i]);
        cout << "Средний балл: " << getAverageRating(group[i]) << "\n\n";
    }

    cout << "Студенты со средним баллом > 4.0:\n";
    for (int i = 0; i < 4; i++) {
        if (getAverageRating(group[i]) > 4.0) {
            cout << "- " << group[i].fio << " (ср. балл = " << getAverageRating(group[i]) << ")\n";
        }
    }

    return 0;
}
