#include <iostream>
using namespace std;

struct Complex {
    double real;  
    double imag;  
};

Complex add(Complex a, Complex b) {
    return {a.real + b.real, a.imag + b.imag};
}

Complex subtract(Complex a, Complex b) {
    return {a.real - b.real, a.imag - b.imag};
}

Complex multiply(Complex a, Complex b) {
    return {a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real};
}

void print(Complex c) {
    cout << "(" << c.real;
    if (c.imag >= 0)
        cout << " + " << c.imag << "i)";
    else
        cout << " - " << -c.imag << "i)";
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    Complex x, y;

    cout << "Введите первое комплексное число (действительная и мнимая часть): ";
    cin >> x.real >> x.imag;

    cout << "Введите второе комплексное число (действительная и мнимая часть): ";
    cin >> y.real >> y.imag;

    cout << "\n Первое число: ";
    print(x);
    cout << "\n Второе число: ";
    print(y);

    cout << "\n\n Сложение: ";
    print(add(x, y));

    cout << "\n Вычитание: ";
    print(subtract(x, y));

    cout << "\n Умножение: ";
    print(multiply(x, y));

    cout << endl;
    return 0;
}
