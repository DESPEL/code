#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Stack {
public:
    Stack() { max_sz = 1; }
    Stack(size_t maxSize) { max_sz = maxSize; }
    ~Stack() { delete[] stackBuff; }

    void push(T val) {
        idx++;
        if (idx == max_sz)
            resizeBuffer(idx + 1);
        stackBuff[idx] = val;
    }

    void pop() { idx == 0 ? idx = 0 : idx--; }

    T top() { return stackBuff[idx]; }

    bool empty() { return idx == 0; }

    void resizeBuffer(size_t newSize) {
        T *tempBuff = new T[newSize];
        for (int i = 0; i < max_sz; i++) {
            tempBuff[i] = stackBuff[i];
        }
        delete[] stackBuff;
        max_sz = newSize;
        stackBuff = tempBuff;
    }

    template <typename T2>
    friend std::ostream &operator<<(std::ostream &out, const Stack<T2> &stack);

private:
    size_t max_sz;
    T *stackBuff = new T[max_sz];
    int idx = 0;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const Stack<T> &stack) {
    std::string elements = "{ ";
    for (int i = 0; i < stack.idx; i++) {
        elements += to_string(stack.stackBuff[i]);
        elements += (i == stack.idx - 1) ? " }" : ", ";
    }
    return out << elements;
}

template <typename T, size_t max_sz = 5>
class Queue {
public:
    Queue() {
        buffer = new T[max_sz];
        tail = 0;
        head = 0;
    }
    ~Queue() { delete[] buffer; }

    void enqueue(T element) {
        buffer[tail] = element;
        tail = (tail + 1) % max_sz;
    }

    T front() { return buffer[head]; }
    void dequeue() { head = (head + 1) % max_sz; }

    template <typename T2, size_t sz>
    friend std::ostream &operator<<(std::ostream &out,
                                    const Queue<T2, sz> &queue);

private:
    T *buffer;
    int tail;
    int head;
};

template <typename T, size_t sz>
std::ostream &operator<<(std::ostream &out, const Queue<T, sz> &queue) {
    std::string elements = "{ ";
    for (int i = queue.head; i < queue.tail % sz; i = (i + 1) % sz) {
        elements += to_string(queue.buffer[i]);
        elements += (i < queue.tail - 1) ? ", " : " }";
    }
    return out << elements;
}

int main() {
    Queue<int, 10> prueba;
    prueba.enqueue(5);
    prueba.enqueue(6);
    prueba.enqueue(7);
    prueba.enqueue(8);
    prueba.dequeue();

    std::cout << prueba.front();
}
