#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <stdexcept>

class Shape {
protected:
    std::string color_;
    std::string name_;
public:
    Shape(std::string n, std::string c) : color_(std::move(c)), name_(std::move(n)) {}
    virtual ~Shape() = default;

    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void draw() const = 0;

    virtual void displayInfo() const {
        std::cout << "Фигура: " << name_ << ", Цвет: " << color_ << "\n";
    }
};

class Circle : public Shape {
    double r_;
public:
    Circle(std::string c, double r) : Shape("Круг", std::move(c)), r_(r) {
        if (r_ <= 0) throw std::invalid_argument("Радиус > 0");
    }
    double calculateArea() const override { return M_PI * r_ * r_; }
    double calculatePerimeter() const override { return 2 * M_PI * r_; }
    void draw() const override { std::cout << "Рисуем круг радиуса " << r_ << "\n"; }
};

class Rectangle : public Shape {
    double w_, h_;
public:
    Rectangle(std::string c, double w, double h) : Shape("Прямоугольник", std::move(c)), w_(w), h_(h) {
        if (w_ <= 0 || h_ <= 0) throw std::invalid_argument("Стороны > 0");
    }
    double calculateArea() const override { return w_ * h_; }
    double calculatePerimeter() const override { return 2 * (w_ + h_); }
    void draw() const override { std::cout << "Рисуем прямоугольник " << w_ << "x" << h_ << "\n"; }
};

class Triangle : public Shape {
    double a_, b_, c_;
public:
    Triangle(std::string color, double a, double b, double c)
        : Shape("Треугольник", std::move(color)), a_(a), b_(b), c_(c) {
        if (a_ <= 0 || b_ <= 0 || c_ <= 0 || a_ + b_ <= c_ || a_ + c_ <= b_ || b_ + c_ <= a_)
            throw std::invalid_argument("Некорректные стороны треугольника");
    }
    double calculatePerimeter() const override { return a_ + b_ + c_; }
    double calculateArea() const override {
        double p = calculatePerimeter() / 2.0;
        return std::sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }
    void draw() const override { std::cout << "Рисуем треугольник со сторонами " << a_ << "," << b_ << "," << c_ << "\n"; }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_unique<Circle>("Красный", 5.0));
    shapes.emplace_back(std::make_unique<Rectangle>("Синий", 4.0, 6.0));
    shapes.emplace_back(std::make_unique<Triangle>("Зеленый", 3.0, 4.0, 5.0));

    for (const auto& sh : shapes) {
        sh->displayInfo();
        sh->draw();
        std::cout << "Периметр: " << sh->calculatePerimeter()
                  << ", Площадь: " << sh->calculateArea() << "\n\n";
    }
    return 0;
}
