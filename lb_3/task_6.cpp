#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string ownerName;
    double balance;
    static int totalAccounts;          
    static double totalBankBalance;   
    const double MIN_BALANCE = 10.0;   

public:
    BankAccount(string accNum, string owner, double initialBalance)
        : accountNumber(accNum), ownerName(owner), balance(initialBalance) {
        totalAccounts++;
        totalBankBalance += balance;
        cout << "Создан счёт: " << accountNumber << " (" << ownerName << "), баланс: " << balance << " руб.\n";
    }

    ~BankAccount() {
        cout << "Закрывается счёт: " << accountNumber << " (" << ownerName << "), остаток: " << balance << " руб.\n";
        totalAccounts--;
        totalBankBalance -= balance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Ошибка: сумма пополнения должна быть положительной.\n";
            return;
        }
        balance += amount;
        totalBankBalance += amount;
        cout << ownerName << " пополнил счёт на " << amount << " руб. Новый баланс: " << balance << " руб.\n";
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Ошибка: сумма снятия должна быть положительной.\n";
            return;
        }
        if (balance - amount < MIN_BALANCE) {
            cout << "Ошибка: нельзя снять " << amount
                 << " руб. Минимальный остаток должен быть не менее " << MIN_BALANCE << " руб.\n";
            return;
        }
        balance -= amount;
        totalBankBalance -= amount;
        cout << ownerName << " снял " << amount << " руб. Остаток: " << balance << " руб.\n";
    }

    void displayAccountInfo() const {
        cout << "Номер счёта: " << accountNumber << endl;
        cout << "Владелец: " << ownerName << endl;
        cout << "Баланс: " << balance << " руб." << endl;
        cout << "\n";
    }


    static int getTotalAccounts() {
        return totalAccounts;
    }

    static double getTotalBankBalance() {
        return totalBankBalance;
    }

    static double getAverageBalance() {
        return (totalAccounts > 0) ? totalBankBalance / totalAccounts : 0.0;
    }
};

int BankAccount::totalAccounts = 0;
double BankAccount::totalBankBalance = 0.0;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    cout << " Открытие счетов\n";
    BankAccount acc1("12345", "Иван Иванов", 500.0);
    BankAccount acc2("67890", "Петр Петров", 1500.0);
    BankAccount acc3("54321", "Анна Смирнова", 2000.0);

    cout << "\n Состояние банка \n";
    cout << "Всего счетов: " << BankAccount::getTotalAccounts() << endl;
    cout << "Общий баланс банка: " << BankAccount::getTotalBankBalance() << " руб.\n";
    cout << "Средний баланс по счетам: " << BankAccount::getAverageBalance() << " руб.\n";

    cout << "\nОперации со счетами\n";
    acc1.deposit(250);
    acc2.withdraw(300);
    acc3.withdraw(1900);

    cout << "\n Информация о каждом счёте\n";
    acc1.displayAccountInfo();
    acc2.displayAccountInfo();
    acc3.displayAccountInfo();

    cout << "\n Итог по банку после операций \n";
    cout << "Всего счетов: " << BankAccount::getTotalAccounts() << endl;
    cout << "Общий баланс банка: " << BankAccount::getTotalBankBalance() << " руб.\n";
    cout << "Средний баланс: " << BankAccount::getAverageBalance() << " руб.\n";

    cout << "\n Закрытие счетов \n";

    return 0;
}
