#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Vehicle {
protected:
    std::string brand_, model_;
    int year_;
    double fuel_{100.0};
    bool engineOn_{false};

public:
    Vehicle(std::string b, std::string m, int y) : brand_(std::move(b)), model_(std::move(m)), year_(y) {}
    virtual ~Vehicle() = default;

    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;
    virtual void refuel(double amount) = 0;

    virtual void displayInfo() const {
        std::cout << brand_ << " " << model_ << " (" << year_ << ")\n"
                  << "Топливо: " << fuel_ << "%, Двигатель: " << (engineOn_ ? "вкл" : "выкл") << "\n";
    }

    double fuelLevel() const { return fuel_; }
};

class Car : public Vehicle {
    int doors_{};
    std::string transmission_;
public:
    Car(std::string b, std::string m, int y, int d, std::string tr)
        : Vehicle(std::move(b), std::move(m), y), doors_(d), transmission_(std::move(tr)) {}

    void startEngine() override { engineOn_ = true; std::cout << "Авто завелось.\n"; }
    void stopEngine() override { engineOn_ = false; std::cout << "Авто заглушено.\n"; }
    void refuel(double amount) override {
        if (amount <= 0) return;
        fuel_ = std::min(100.0, fuel_ + amount);
    }

    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "Дверей: " << doors_ << ", КПП: " << transmission_ << "\n";
    }
};

class Motorcycle : public Vehicle {
    bool hasFairing_{};
public:
    Motorcycle(std::string b, std::string m, int y, bool fairing)
        : Vehicle(std::move(b), std::move(m), y), hasFairing_(fairing) {}
    void startEngine() override { engineOn_ = true; std::cout << "Мотоцикл завелся.\n"; }
    void stopEngine() override { engineOn_ = false; std::cout << "Мотоцикл заглушен.\n"; }
    void refuel(double amount) override {
        if (amount <= 0) return;
        fuel_ = std::min(100.0, fuel_ + amount);
    }
    void wheelie() const { std::cout << brand_ << " " << model_ << " делает вилли!\n"; }

    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "Обтекатели: " << (hasFairing_ ? "есть" : "нет") << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    std::vector<std::unique_ptr<Vehicle>> park;
    park.emplace_back(std::make_unique<Car>("Toyota", "Camry", 2021, 4, "AT"));
    park.emplace_back(std::make_unique<Motorcycle>("Yamaha", "MT-07", 2020, true));

    for (auto& v : park) {
        v->displayInfo();
        v->startEngine();
        v->refuel(-5);  
        v->refuel(15);
        v->displayInfo();
        v->stopEngine();
        std::cout << "\n";
    }
    return 0;
}
