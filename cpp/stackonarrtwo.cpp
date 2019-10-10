#include <iostream>
#include <sstream>
#include <string>

template <typename T>
std::string to_string(const T& n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
}

int main() { std::cout << to_string(5); }