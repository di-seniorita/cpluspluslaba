#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Stack {
    std::vector<T> data_;
    int capacity_;
public:
    explicit Stack(int cap = 10) : capacity_(cap) { data_.reserve(capacity_); }

    void push(const T& x) {
        if (isFull()) throw std::overflow_error("Stack overflow");
        data_.push_back(x);
    }
    T pop() {
        if (isEmpty()) throw std::underflow_error("Stack underflow");
        T x = data_.back(); data_.pop_back(); return x;
    }
    const T& top() const {
        if (isEmpty()) throw std::underflow_error("Empty stack");
        return data_.back();
    }
    bool isEmpty() const { return data_.empty(); }
    bool isFull() const { return static_cast<int>(data_.size()) >= capacity_; }
    int size() const { return static_cast<int>(data_.size()); }

    void display() const {
        std::cout << "Стек: ";
        for (const auto& e : data_) std::cout << e << ' ';
        std::cout << "\n";
    }
};

template<typename T>
class Queue {
    std::vector<T> data_;
    int head_{0}, tail_{0}, count_{0}, capacity_;
public:
    explicit Queue(int cap = 10) : data_(cap), capacity_(cap) {}

    void enqueue(const T& x) {
        if (isFull()) throw std::overflow_error("Queue overflow");
        data_[tail_] = x;
        tail_ = (tail_ + 1) % capacity_;
        ++count_;
    }
    T dequeue() {
        if (isEmpty()) throw std::underflow_error("Queue underflow");
        T x = data_[head_];
        head_ = (head_ + 1) % capacity_;
        --count_;
        return x;
    }
    const T& front() const {
        if (isEmpty()) throw std::underflow_error("Empty queue");
        return data_[head_];
    }
    bool isEmpty() const { return count_ == 0; }
    bool isFull() const { return count_ == capacity_; }
    int size() const { return count_; }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    Stack<int> si(5); si.push(1); si.push(2); si.push(3); si.display(); std::cout << si.pop() << "\n";
    Stack<std::string> ss(3); ss.push("a"); ss.push("b"); ss.display();

    Queue<double> qd(3); qd.enqueue(1.1); qd.enqueue(2.2); std::cout << qd.dequeue() << "\n";
    Queue<std::string> qs(2); qs.enqueue("x"); std::cout << qs.front() << "\n";
    return 0;
}
