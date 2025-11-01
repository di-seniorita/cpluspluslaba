#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string brand;
    string model;
    int year;
    double fuelLevel;

public:
    Vehicle(string b, string m, int y) : brand(b), model(m), year(y), fuelLevel(100) {}
    virtual ~Vehicle() {}

    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;
    virtual void refuel(double amount) = 0;

    virtual void displayInfo() const {
        cout << brand << " " << model << " (" << year << ")" << endl;
        cout << "Уровень топлива: " << fuelLevel << "%" << endl;
    }

    double getFuelLevel() const { return fuelLevel; }

    void setFuelLevel(double level) {
        if (level >= 0 && level <= 100)
            fuelLevel = level;
    }
};

class Car : public Vehicle {
private:
    int doors;
    string transmission;

public:
    Car(string b, string m, int y, int d, string trans)
        : Vehicle(b, m, y), doors(d), transmission(trans) {}

    void startEngine() override {
        cout << brand << " " << model << ": двигатель запущен (автомобиль)." << endl;
    }

    void stopEngine() override {
        cout << brand << " " << model << ": двигатель остановлен." << endl;
    }

    void refuel(double amount) override {
        fuelLevel += amount;
        if (fuelLevel > 100)
            fuelLevel = 100;
        cout << brand << " " << model << " заправлен. Топливо: " << fuelLevel << "%" << endl;
    }

    void displayInfo() const override {
        cout << "Автомобиль: " << brand << " " << model << " (" << year << ")" << endl;
        cout << "Дверей: " << doors << ", КПП: " << transmission
             << ", Топливо: " << fuelLevel << "%" << endl;
    }
};

class Motorcycle : public Vehicle {
private:
    bool hasFairing;

public:
    Motorcycle(string b, string m, int y, bool fairing)
        : Vehicle(b, m, y), hasFairing(fairing) {}

    void startEngine() override {
        cout << brand << " " << model << ": двигатель запущен (мотоцикл)." << endl;
    }

    void stopEngine() override {
        cout << brand << " " << model << ": двигатель остановлен." << endl;
    }

    void refuel(double amount) override {
        fuelLevel += amount;
        if (fuelLevel > 100)
            fuelLevel = 100;
        cout << brand << " " << model << " заправлен. Топливо: " << fuelLevel << "%" << endl;
    }

    void wheelie() {
        cout << brand << " " << model << " делает вилли!" << endl;
    }

    void displayInfo() const override {
        cout << "Мотоцикл: " << brand << " " << model << " (" << year << ")" << endl;
        cout << "Обтекатель: " << (hasFairing ? "есть" : "нет")
             << ", Топливо: " << fuelLevel << "%" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    vector<Vehicle*> garage;

    garage.push_back(new Car("Toyota", "Camry", 2022, 4, "Автомат"));
    garage.push_back(new Motorcycle("Yamaha", "R6", 2020, true));

    cout << "Информация о транспорте" << endl;
    for (auto v : garage) {
        v->displayInfo(); 
        v->startEngine();
        v->refuel(10);
        v->stopEngine();
    }

    Motorcycle* moto = dynamic_cast<Motorcycle*>(garage[1]);
    if (moto) {
        moto->wheelie();
    }

    for (auto v : garage) {
        delete v;
    }

    return 0;
}
