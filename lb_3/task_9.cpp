#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
class Stack {
private:
    vector<T> elements;
    int capacity;

public:
    Stack(int size = 10) : capacity(size) {}
    
    void push(const T& element) {
        if (isFull()) throw overflow_error("Стек переполнен");
        elements.push_back(element);
    }

    T pop() {
        if (isEmpty()) throw underflow_error("Стек пуст");
        T value = elements.back();
        elements.pop_back();
        return value;
    }

    T top() const {
        if (isEmpty()) throw underflow_error("Стек пуст");
        return elements.back();
    }

    bool isEmpty() const { return elements.empty(); }
    bool isFull() const { return elements.size() >= capacity; }

    int size() const { return elements.size(); }
    
    void display() const {
        cout << "Стек: ";
        for (const auto& elem : elements) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

template<typename T>
class Queue {
private:
    vector<T> elements;
    int capacity;

public:
    Queue(int size = 10) : capacity(size) {}
    
    void enqueue(const T& element) {
        if (isFull()) throw overflow_error("Очередь переполнена");
        elements.push_back(element);
    }

    T dequeue() {
        if (isEmpty()) throw underflow_error("Очередь пуста");
        T value = elements.front();
        elements.erase(elements.begin());
        return value;
    }

    T front() const {
        if (isEmpty()) throw underflow_error("Очередь пуста");
        return elements.front();
    }

    bool isEmpty() const { return elements.empty(); }
    bool isFull() const { return elements.size() >= capacity; }

    int size() const { return elements.size(); }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    try {
        Stack<int> intStack(5);
        intStack.push(10);
        intStack.push(20);
        intStack.push(30);
        intStack.display();
        cout << "Верхний элемент: " << intStack.top() << endl;
        cout << "Извлекаем: " << intStack.pop() << endl;
        intStack.display();

        Stack<string> strStack(3);
        strStack.push("C++");
        strStack.push("Python");
        strStack.display();
        cout << "Извлекаем: " << strStack.pop() << endl;
        strStack.display();

        Queue<double> dblQueue(4);
        dblQueue.enqueue(1.1);
        dblQueue.enqueue(2.2);
        dblQueue.enqueue(3.3);
        cout << "Первый элемент: " << dblQueue.front() << endl;
        cout << "Удаляем: " << dblQueue.dequeue() << endl;
        cout << "Размер очереди: " << dblQueue.size() << endl;

        Queue<string> strQueue(3);
        strQueue.enqueue("Alice");
        strQueue.enqueue("Bob");
        cout << "Первый элемент: " << strQueue.front() << endl;
        cout << "Удаляем: " << strQueue.dequeue() << endl;
        cout << "Размер очереди: " << strQueue.size() << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
