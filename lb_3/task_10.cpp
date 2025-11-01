#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class UniversityMember {
protected:
    std::string name_, id_, email_;
public:
    UniversityMember(std::string n, std::string i, std::string e)
        : name_(std::move(n)), id_(std::move(i)), email_(std::move(e)) {}
    virtual ~UniversityMember() = default;

    virtual void displayInfo() const = 0;
    virtual void work() const = 0;
    virtual std::string getRole() const = 0;

    const std::string& id() const { return id_; }
    const std::string& name() const { return name_; }
};

class Student : public UniversityMember {
    std::string major_;
    int year_{};
    double gpa_{};
    std::vector<std::string> courses_;
public:
    Student(std::string n, std::string i, std::string e, std::string major, int year)
        : UniversityMember(std::move(n), std::move(i), std::move(e)),
          major_(std::move(major)), year_(year) {}

    void enrollCourse(const std::string& c) { courses_.push_back(c); }
    void dropCourse(const std::string& c) {
        courses_.erase(std::remove(courses_.begin(), courses_.end(), c), courses_.end());
    }
    void setGPA(double g) { gpa_ = g; }

    void displayInfo() const override {
        std::cout << "[Студент] " << name_ << " (" << id_ << ") " << major_
                  << ", курс: " << year_ << ", GPA: " << gpa_ << "\nКурсы: ";
        for (const auto& c : courses_) std::cout << c << ' '; std::cout << "\n";
    }
    void work() const override { std::cout << "Ходит на пары и выполняет задания\n"; }
    std::string getRole() const override { return "Student"; }
};

class Professor : public UniversityMember {
    std::string department_, office_;
    double salary_{};
    std::vector<std::string> teachingCourses_;
public:
    Professor(std::string n, std::string i, std::string e, std::string dept, std::string office, double sal)
        : UniversityMember(std::move(n), std::move(i), std::move(e)),
          department_(std::move(dept)), office_(std::move(office)), salary_(sal) {}

    void assignCourse(const std::string& c) { teachingCourses_.push_back(c); }
    void removeCourse(const std::string& c) {
        teachingCourses_.erase(std::remove(teachingCourses_.begin(), teachingCourses_.end(), c), teachingCourses_.end());
    }
    double calculateSalary() const { return salary_; }

    void displayInfo() const override {
        std::cout << "[Профессор] " << name_ << " (" << id_ << ") " << department_
                  << ", кабинет: " << office_ << ", зарплата: " << salary_ << "\nКурсы: ";
        for (const auto& c : teachingCourses_) std::cout << c << ' '; std::cout << "\n";
    }
    void work() const override { std::cout << "Читает лекции и ведет исследования\n"; }
    std::string getRole() const override { return "Professor"; }
};

class Course {
    std::string code_, name_;
    int credits_{};
    Professor* instructor_{nullptr};
    std::vector<Student*> students_;
public:
    Course(std::string code, std::string name, int credits)
        : code_(std::move(code)), name_(std::move(name)), credits_(credits) {}

    void setInstructor(Professor* p) { instructor_ = p; }
    void addStudent(Student* s) { students_.push_back(s); }
    void removeStudent(const std::string& sid) {
        students_.erase(std::remove_if(students_.begin(), students_.end(),
            [&](Student* s){ return s->id() == sid; }), students_.end());
    }

    void displayCourseInfo() const {
        std::cout << code_ << " — " << name_ << " (" << credits_ << " кр.)\n";
        std::cout << "Преподаватель: " << (instructor_ ? instructor_->name() : "не назначен") << "\n";
        std::cout << "Студенты: ";
        for (const auto* s : students_) std::cout << s->name() << ' ';
        std::cout << "\n";
    }
};

class University {
    std::string name_;
    std::vector<std::unique_ptr<UniversityMember>> members_;
    std::vector<std::unique_ptr<Course>> courses_;
    inline static int totalUniversities_ = 0;
public:
    explicit University(std::string n) : name_(std::move(n)) { ++totalUniversities_; }
    ~University() { --totalUniversities_; }

    template<typename T, typename... Args>
    T* addMember(Args&&... args) {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = ptr.get();
        members_.push_back(std::move(ptr));
        return raw;
    }

    Course* addCourse(std::string code, std::string name, int credits) {
        auto ptr = std::make_unique<Course>(std::move(code), std::move(name), credits);
        Course* raw = ptr.get();
        courses_.push_back(std::move(ptr));
        return raw;
    }

    void listMembers() const {
        std::cout << "Члены университета " << name_ << ":\n";
        for (const auto& m : members_) m->displayInfo();
    }

    void listCourses() const {
        std::cout << "Курсы университета:\n";
        for (const auto& c : courses_) c->displayCourseInfo();
    }

    static int totalUniversities() { return totalUniversities_; }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8"); 
    
    University u("Tech University");
    auto* s1 = u.addMember<Student>("Иван", "S001", "s1@u.edu", "CS", 2);
    auto* s2 = u.addMember<Student>("Мария", "S002", "s2@u.edu", "CS", 3);
    auto* p1 = u.addMember<Professor>("Доктор Петров", "P001", "p1@u.edu", "CS Dept", "B-204", 120000);

    s1->setGPA(4.6); s1->enrollCourse("CS101");
    s2->setGPA(4.2); s2->enrollCourse("CS101");

    auto* cs101 = u.addCourse("CS101", "OOP in C++", 4);
    cs101->setInstructor(p1);
    cs101->addStudent(s1);
    cs101->addStudent(s2);
    p1->assignCourse("CS101");

    u.listMembers();
    std::cout << "\n";
    u.listCourses();
    std::cout << "Всего университетов: " << University::totalUniversities() << "\n";
    return 0;
}
