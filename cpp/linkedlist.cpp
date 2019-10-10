#include <iostream>
#include <sstream>
#include <string>

template <typename T>
std::string to_string(T val) {
    std::ostringstream v;
    v << val;
    std::cout << "asd: " << v.str() << std::endl;
    return v.str();
}

template <typename T>
struct ListElement {
    ListElement(){};
    ListElement(T d) { data = d; };
    T data;
    ListElement *next = nullptr;
};

template <typename T>
class SinglyLinkedList {
protected:
    ListElement<T> *head = new ListElement<T>;
    ListElement<T> *last = head;

public:
    void insert(T data) {
        if (head == last) {
            head->data = data;
            return;
        }
        ListElement<T> *temp = new ListElement<T>(data);
        last->next = temp;
        last = temp;
        return;
    }

    // O(n) complexity
    void pop() {
        if (head->next == nullptr)
            return;
        ListElement<T> *temp = head;
        ListElement<T> *plast;

        delete last;
        while (temp->next != nullptr) {
            plast = temp;
            temp->next;
        }

        plast->next = nullptr;
        last = plast;
        return;
    }

    void join(SinglyLinkedList<T> lista) {
        ListElement<T> *a = lista.head;
        last->next = a;
    }

    ListElement<T> *find(T data) {
        ListElement<T> *actual = head;
        while (actual->next != nullptr) {
            if (actual->data == data)
                return actual;
            actual = actual->next;
        }
        return nullptr;
    }

    template <typename T2>
    friend std::ostream &operator<<(std::ostream &out,
                                    const SinglyLinkedList<T2> &data);
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const SinglyLinkedList<T> &data) {
    std::string elementos = "{ ";
    ListElement<T> *actual = data.head;
    while (true) {
        std::cout << actual->data << std::endl;
        elementos += to_string(actual->data);
        elementos += (actual->next == nullptr) ? " }" : ", ";
        std::cout << "next: " << actual->next << std::endl;
        if (actual->next != nullptr)
            break;
        actual = actual->next;
    }

    return out << data;
}

template <typename T>
class Stack : public SinglyLinkedList<T> {
public:
    void push(T data) {
        ListElement<T> *newHead = new ListElement<T>(data);
        newHead->next = this->head;
        this->head = newHead;
    }

    void pop() {
        ListElement<T> *newHead = this->head->next;
        delete this->head;
        this->head = newHead;
    }

    T top() { return this->head->data; }
};

template <typename T>
class Queue : SinglyLinkedList<T> {
public:
    void enqueue(T data) {
        ListElement<T> *newLast = new ListElement<T>();
        this->last->next = newLast;
        this->last->data = data;
        this->last = newLast;
    }

    void dequeue() {
        ListElement<T> *newHead = this->head->next;
        delete this->head;
        this->head = newHead;
    }

    T front() { return this->head->data; }
};

int main() {
    SinglyLinkedList<int> a;
    SinglyLinkedList<int> b;
    b.insert(1);
    std::cout << b << std::endl;
    a.join(b);
    // std::cout << a;
}