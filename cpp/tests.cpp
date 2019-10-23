#include <iostream>
#include <utility>
#include <vector>

constexpr int p1(const int &x) { return 5; }

template <typename T>
constexpr T test(const T &v1, const T &v2) {
    if (v1 > v2)
        return v1;
    return v2;
}

template <typename T>
auto lmbdsum(T) {
    return [](const T &a, const T &b) { return a + b; };
}

template <typename T>
auto csumlmbd(T v1) {
    return [=](const T &a) { return v1 + a; };
}

template <typename T>
T sum(const T &a, const T &b) {
    return a + b;
}

// http://thbecker.net/articles/rvalue_references/section_03.html
template <typename T>
void print(T &&var) {  //  Rvalue reference
    std::cout << var << '\n';
}

template <typename T>
class C {
private:
    std::vector<T> *container = new std::vector<T>();

public:
    C() {}
    C(int size) { container->resize(size); }
    C(C<T> &&element) {
        if (this != &element) {
            delete this->container;
            this->container = element.container;
            element.container = nullptr;
        }
    }

    C<T> &operator=(C<T> &&v1) {
        if (this != &v1) {
            delete this->container;
            this->container = v1.container;
            v1.container = nullptr;
        }
        return *this;
    }
};

namespace tests {
template <class C>
void swap(C &a, C &b) {
    C temp(std::move(a));
    a = std::move(b);
    b = std::move(temp);
}
}  // namespace tests

int main() {
    C<int> a(5);
    C<int> b(15);
    tests::swap(a, b);
    return 0;
}