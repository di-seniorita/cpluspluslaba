#include <iostream>
#include <string>
#include <iomanip>

class Complex {
    double re_{}, im_{};

public:
    Complex(double r = 0, double i = 0) : re_(r), im_(i) {}

    double real() const { return re_; }
    double imag() const { return im_; }
    void setReal(double r) { re_ = r; }
    void setImag(double i) { im_ = i; }

    Complex operator+(const Complex& o) const { return {re_ + o.re_, im_ + o.im_}; }
    Complex operator-(const Complex& o) const { return {re_ - o.re_, im_ - o.im_}; }
    Complex operator*(const Complex& o) const { return {re_ * o.re_ - im_ * o.im_, re_ * o.im_ + im_ * o.re_}; }
    bool operator==(const Complex& o) const { return re_ == o.re_ && im_ == o.im_; }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.re_ << (c.im_ >= 0 ? " + " : " - ") << std::abs(c.im_) << "i";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Complex& c) {
        // формат: re im
        return is >> c.re_ >> c.im_;
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    Complex a(2, 3), b(1, -4);
    Complex c = a + b;
    Complex d = a - b;
    Complex e = a * b;

    std::cout << "a = " << a << "\nb = " << b << "\n";
    std::cout << "a + b = " << c << "\n";
    std::cout << "a - b = " << d << "\n";
    std::cout << "a * b = " << e << "\n";

    std::cout << "Введите комплексное число (re im): ";
    Complex x;
    if (std::cin >> x) std::cout << "Вы ввели: " << x << "\n";
    return 0;
}
