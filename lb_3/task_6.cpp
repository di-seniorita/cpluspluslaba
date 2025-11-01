#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>

class BankAccount {
    std::string accountNumber_;
    std::string ownerName_;
    double balance_{};
    inline static int totalAccounts_ = 0;
    inline static double totalBankBalance_ = 0.0;
    static constexpr double MIN_BALANCE_ = 10.0;

public:
    BankAccount(std::string acc, std::string owner, double initial)
        : accountNumber_(std::move(acc)), ownerName_(std::move(owner)), balance_(initial) {
        if (initial < MIN_BALANCE_) throw std::invalid_argument("Начальный баланс ниже минимума");
        ++totalAccounts_;
        totalBankBalance_ += balance_;
    }

    ~BankAccount() {
        totalBankBalance_ -= balance_;
        --totalAccounts_;
    }

    void deposit(double amount) {
        if (amount <= 0) throw std::invalid_argument("Пополнение > 0");
        balance_ += amount;
        totalBankBalance_ += amount;
    }

    bool withdraw(double amount) {
        if (amount <= 0) return false;
        if (balance_ - amount < MIN_BALANCE_) return false;
        balance_ -= amount;
        totalBankBalance_ -= amount;
        return true;
    }

    void displayAccountInfo() const {
        std::cout << "[" << accountNumber_ << "] " << ownerName_
                  << " — баланс: " << std::fixed << std::setprecision(2) << balance_ << "\n";
    }

    static int getTotalAccounts() { return totalAccounts_; }
    static double getTotalBankBalance() { return totalBankBalance_; }
    static double getAverageBalance() {
        return totalAccounts_ ? totalBankBalance_ / totalAccounts_ : 0.0;
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    {
        BankAccount a("ACC001", "Иванов", 1000);
        BankAccount b("ACC002", "Петров", 500);
        a.deposit(250);
        b.withdraw(200);
        a.displayAccountInfo();
        b.displayAccountInfo();

        std::cout << "Всего счетов: " << BankAccount::getTotalAccounts() << "\n";
        std::cout << "Суммарный баланс: " << BankAccount::getTotalBankBalance() << "\n";
        std::cout << "Средний баланс: " << BankAccount::getAverageBalance() << "\n";
    }
    std::cout << "После выхода из области — Всего счетов: " << BankAccount::getTotalAccounts()
              << ", Сумма: " << BankAccount::getTotalBankBalance() << "\n";
    return 0;
}
