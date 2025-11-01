#include <iostream>
#include <string>
#include <array>
#include <iomanip>

class Student {
private:
    std::string name_;
    int age_{};
    std::array<int, 5> grades_{};

    static bool validGrade(int g) { return g >= 2 && g <= 5; }

public:
    Student(std::string name, int age) : name_(std::move(name)) {
        setAge(age);
        grades_.fill(0);
    }

    const std::string& name() const { return name_; }
    int age() const { return age_; }

    void setName(const std::string& n) {
        if (n.empty()) throw std::invalid_argument("Имя не может быть пустым");
        name_ = n;
    }
    void setAge(int a) {
        if (a < 14 || a > 100) throw std::out_of_range("Возраст вне диапазона");
        age_ = a;
    }

    void setGrade(size_t idx, int value) {
        if (idx >= grades_.size()) throw std::out_of_range("Индекс оценки");
        if (!validGrade(value)) throw std::invalid_argument("Оценка должна быть 2..5");
        grades_[idx] = value;
    }

    double calcAverage() const {
        int sum = 0;
        for (int g : grades_) sum += g;
        return static_cast<double>(sum) / grades_.size();
    }

    bool hasScholarship() const { return calcAverage() >= 4.5; }

    void displayInfo() const {
        std::cout << "Студент: " << name_ << ", возраст: " << age_ << "\nОценки: ";
        for (int g : grades_) std::cout << g << ' ';
        std::cout << "\nСредний балл: " << std::fixed << std::setprecision(2) << calcAverage() << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    Student student("Иван Иванов", 20);
    student.setGrade(0, 5);
    student.setGrade(1, 4);
    student.setGrade(2, 5);
    student.setGrade(3, 3);
    student.setGrade(4, 4);

    student.displayInfo();
    std::cout << (student.hasScholarship() ? "Студент получает стипендию\n" : "Стипендия не назначена\n");
    return 0;
}
