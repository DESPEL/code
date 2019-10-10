#include <iostream>
#include <sstream>
#include <string>

template <typename T>
std::string to_string(const T &n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
}

template <typename T, size_t max_sz>
class DoubleStack {
    T *dstack = new T[max_sz];
    int idxr = 0;
    int idxl = max_sz - 1;

    bool overlap() { return (idxr - 1) == (idxl + 1); }

public:
    void insertr(T item) {
        if (overlap())
            return;
        dstack[idxr] = item;
        idxr++;
    }
    void insertl(T item) {
        if (overlap())
            return;
        dstack[idxl] = item;
        idxl--;
    }

    void popr() {
        if (idxr == 0)
            return;
        idxr--;
    }
    void popl() {
        if (idxl == (max_sz - 1))
            return;
        idxl++;
    }

    bool emptyr() { return idxr == 0; }
    bool emptyl() { return idxl == (max_sz - 1); }

    template <typename T2, size_t sz>
    friend std::ostream &operator<<(std::ostream &out,
                                    const DoubleStack<T2, sz> &dstack);
};

template <typename T, size_t sz>
std::ostream &operator<<(std::ostream &out, const DoubleStack<T, sz> &dstack) {
    std::string elements = "{ ";
    for (int i = 0; i < dstack.idxr; i++) {
        elements += to_string(dstack.dstack[i]);
        elements += (i < dstack.idxr - 1) ? ", " : "";
    }
    elements += " }, { ";
    for (int i = sz - 1; i > dstack.idxl; i--) {
        elements += to_string(dstack.dstack[i]);
        elements += (i > (dstack.idxl + 1)) ? ", " : "";
    }
    elements += " }";
    return out << elements;
}

int main() {
    DoubleStack<int, 10> prueba;
    prueba.insertl(1);
    prueba.insertr(5);
    prueba.popr();
    prueba.insertr(8);
    std::cout << prueba;
}
