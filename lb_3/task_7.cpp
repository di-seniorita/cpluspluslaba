#include <iostream>
#include <string>
using namespace std;

class Complex {
private:
    double real;
    double imaginary;

public:
    Complex(double r = 0, double i = 0) : real(r), imaginary(i) {}

    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }
    void setReal(double r) { real = r; }
    void setImaginary(double i) { imaginary = i; }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }

    Complex operator*(const Complex& other) const {
        double newReal = real * other.real - imaginary * other.imaginary;
        double newImag = real * other.imaginary + imaginary * other.real;
        return Complex(newReal, newImag);
    }

    bool operator==(const Complex& other) const {
        return (real == other.real && imaginary == other.imaginary);
    }

    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);

    void display() const {
        cout << real << " + " << imaginary << "i" << endl;
    }
};

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real;
    if (c.imaginary >= 0)
        os << " + " << c.imaginary << "i";
    else
        os << " - " << -c.imaginary << "i";
    return os;
}

istream& operator>>(istream& is, Complex& c) {
    cout << "Введите действительную часть: ";
    is >> c.real;
    cout << "Введите мнимую часть: ";
    is >> c.imaginary;
    return is;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    Complex c1(3, 4);
    Complex c2(1, -2);
    Complex c3;

    cout << "Начальные числа" << endl;
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;

    cout << "\n Арифметические операции" << endl;
    c3 = c1 + c2;
    cout << "c1 + c2 = " << c3 << endl;

    c3 = c1 - c2;
    cout << "c1 - c2 = " << c3 << endl;

    c3 = c1 * c2;
    cout << "c1 * c2 = " << c3 << endl;

    cout << "\n Проверка равенства " << endl;
    cout << "c1 == c2 ? " << (c1 == c2 ? "Да" : "Нет") << endl;

    cout << "\n Ввод нового комплексного числа" << endl;
    Complex userComplex;
    cin >> userComplex;

    cout << "Вы ввели: " << userComplex << endl;

    return 0;
}
