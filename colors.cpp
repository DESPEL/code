#include <iostream>

using namespace std;

template <typename T, size_t N>
struct span {
    T(&arr)[N];
    size_t sz = N;

    span(T (&arr)[N]) : arr(arr), sz(N) {}

    struct iterator {
        iterator(T* pos) : pos(pos) {}
        T* pos;

        T& operator *() { return *pos; }
        void operator ++() { ++pos; }
        void operator --() { --pos; }
        bool operator !=(const iterator& rhs) { return pos != rhs.pos; }
        bool operator ==(const iterator& rhs) { return pos == rhs.pos; }
    };

    struct reverse_iterator {
        reverse_iterator(T* pos) : pos(pos) {}
        T* pos;

        T& operator *() const { return *pos; }
        void operator ++() { --pos; }
        void operator --() { ++pos; }
        bool operator !=(const reverse_iterator& rhs) const { return pos != rhs.pos; }
        bool operator ==(const reverse_iterator& rhs) const { return pos == rhs.pos; }
    };
    

    iterator begin() const { return &arr[0]; }
    iterator end() const { return &arr[size()]; }

    reverse_iterator rbegin() const { return &arr[size() - 1]; }
    reverse_iterator rend() const { return &arr[0] - 1; }

    constexpr auto size() const { return sz; }
};

template <typename Container>
struct Reverse {
    Container& container;
    Reverse(Container& c) : container(c) {}

    typename Container::reverse_iterator begin() { return container.rbegin(); }
    typename Container::reverse_iterator end() { return container.rend(); }
};

using Coord = std::array<int,3>;

Coord getVec3d() { return { 0, 0, 0}}

int main () {
    std::pair<int, string> a = {1, "asd"};

    auto [x, y, z] = getVec3d();

    if (int i = 5; x == x) {
        
    }

    int arr[5] = {1,2,3,4,5};

    span s(arr);
    for (auto& v : Reverse(s)) {
        std::cout << v++ << " ";
    }
    std::cout << '\n';
    for (auto v : s) {
        std::cout << v++ << " ";
    }

}