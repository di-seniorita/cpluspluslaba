#include <iostream>
#include <windows.h>   
using namespace std;

struct Account {
    int number;     
    double balance; 
};

void deposit(Account* acc, double amount) {
    if (amount > 0) {
        acc->balance += amount;
        cout << "На счёт внесено " << amount << " руб.\n";
    } else {
        cout << "Ошибка: внесите деньги, которые существуют\n";
    }
}

void withdraw(Account& acc, double amount) {
    if (amount <= 0) {
        cout << "Ошибка: сумма должна быть больше нуля!\n";
        return;
    }

    if (acc.balance >= amount) {
        acc.balance -= amount;
        cout << "Со счёта снято " << amount << " руб.\n";
    } else {
        cout << "Недостаточно средств! Баланс: " << acc.balance << " руб.\n";
    }
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    Account myAccount;
    cout << "Введите номер счёта: ";
    cin >> myAccount.number;
    myAccount.balance = 10000.0;

    cout << "Счёт №" << myAccount.number << " открыт.\n";
    cout << "Ваш баланс: " << myAccount.balance << " руб.\n\n";

    double addAmount, takeAmount;

    cout << "Введите сумму для пополнения: ";
    cin >> addAmount;
    deposit(&myAccount, addAmount);
    cout << "Баланс после пополнения: " << myAccount.balance << " руб.\n\n";


    cout << "Введите сумму для снятия: ";
    cin >> takeAmount;
    withdraw(myAccount, takeAmount);
    cout << "Баланс после снятия: " << myAccount.balance << " руб.\n\n";

    return 0;
}
