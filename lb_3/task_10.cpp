#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class UniversityMember {
protected:
    string name;
    string id;
    string email;

public:
    UniversityMember(string n, string i, string e) : name(n), id(i), email(e) {}
    virtual ~UniversityMember() {}
    
    virtual void displayInfo() const = 0;
    virtual void work() const = 0;
    virtual string getRole() const = 0;
};

class Student : public UniversityMember {
private:
    string major;
    int year;
    double gpa;
    vector<string> courses;

public:
    Student(string n, string i, string e, string m, int y)
        : UniversityMember(n, i, e), major(m), year(y), gpa(0.0) {}

    void displayInfo() const override {
        cout << "Студент: " << name << ", ID: " << id << ", Email: " << email
             << ", Специальность: " << major << ", Курс: " << year
             << ", GPA: " << gpa << endl;
    }

    void work() const override {
        cout << name << " посещает занятия и выполняет домашние задания." << endl;
    }

    string getRole() const override {
        return "Студент";
    }

    void enrollCourse(const string& course) {
        courses.push_back(course);
        cout << name << " записался на курс: " << course << endl;
    }

    void dropCourse(const string& course) {
        for (size_t i = 0; i < courses.size(); ++i) {
            if (courses[i] == course) {
                courses.erase(courses.begin() + i);
                cout << name << " отчислен с курса: " << course << endl;
                break;
            }
        }
    }

    void calculateGPA() {
        gpa = 4.5; 
    }
};

class Professor : public UniversityMember {
private:
    string department;
    string office;
    double salary;
    vector<string> teachingCourses;

public:
    Professor(string n, string i, string e, string d, string o, double s)
        : UniversityMember(n, i, e), department(d), office(o), salary(s) {}

    void displayInfo() const override {
        cout << "Профессор: " << name << ", ID: " << id << ", Email: " << email
             << ", Кафедра: " << department << ", Кабинет: " << office
             << ", Зарплата: " << salary << endl;
    }

    void work() const override {
        cout << name << " проводит лекции и научные исследования." << endl;
    }

    string getRole() const override {
        return "Профессор";
    }

    void assignCourse(const string& course) {
        teachingCourses.push_back(course);
        cout << name << " назначен преподавателем курса: " << course << endl;
    }

    void removeCourse(const string& course) {
        for (size_t i = 0; i < teachingCourses.size(); ++i) {
            if (teachingCourses[i] == course) {
                teachingCourses.erase(teachingCourses.begin() + i);
                cout << name << " больше не ведёт курс: " << course << endl;
                break;
            }
        }
    }

    double calculateSalary() const {
        return salary;
    }
};

class Course {
private:
    string courseCode;
    string courseName;
    int credits;
    Professor* instructor;
    vector<Student*> enrolledStudents;

public:
    Course(string c, string n, int cr)
        : courseCode(c), courseName(n), credits(cr), instructor(nullptr) {}

    void addStudent(Student* student) {
        enrolledStudents.push_back(student);
        cout << "Студент добавлен на курс: " << courseName << endl;
    }

    void removeStudent(const string& studentId) {
        for (size_t i = 0; i < enrolledStudents.size(); ++i) {
            if (enrolledStudents[i]->getRole() == studentId) {
                enrolledStudents.erase(enrolledStudents.begin() + i);
                break;
            }
        }
    }

    void setInstructor(Professor* prof) {
        instructor = prof;
        cout << "Курс " << courseName << " теперь ведёт профессор." << endl;
    }

    void displayCourseInfo() const {
        cout << "Курс: " << courseCode << " - " << courseName
             << ", Кредиты: " << credits << endl;
        if (instructor != nullptr)
            cout << "Преподаватель назначен." << endl;
        cout << "Количество студентов: " << enrolledStudents.size() << endl;
    }
};

class University {
private:
    string name;
    vector<unique_ptr<UniversityMember>> members;
    vector<unique_ptr<Course>> courses;
    static int totalUniversities;

public:
    University(string n) : name(n) {
        totalUniversities++;
    }
    
    ~University() {
        totalUniversities--;
    }

    void addMember(unique_ptr<UniversityMember> member) {
        members.push_back(move(member));
    }

    void addCourse(unique_ptr<Course> course) {
        courses.push_back(move(course));
    }

    void displayAllMembers() const {
        cout << "\nЧлены университета " << name << ":" << endl;
        for (const auto& m : members)
            m->displayInfo();
    }

    void displayAllCourses() const {
        cout << "\nКурсы университета " << name << ":" << endl;
        for (const auto& c : courses)
            c->displayCourseInfo();
    }

    static int getTotalUniversities() {
        return totalUniversities;
    }
};

int University::totalUniversities = 0;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    University uni("РУДН");

    auto student = make_unique<Student>("Анна Смирнова", "S001", "anna@rudn.ru", "Физика", 2);
    auto professor = make_unique<Professor>("Иван Иванов", "P001", "ivanov@rudn.ru", "Физика", "B-204", 120000);
    auto course = make_unique<Course>("PHY101", "Квантовая механика", 5);

    uni.addMember(move(student));
    uni.addMember(move(professor));
    uni.addCourse(move(course));

    uni.displayAllMembers();
    uni.displayAllCourses();

    cout << "\nВсего университетов: " << University::getTotalUniversities() << endl;

    return 0;
}
