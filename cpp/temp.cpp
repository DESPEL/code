#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <ratio>
#include <vector>

void print(int number) { std::cout << number << ' '; }

std::vector<int> randvector(int min, int max) {
    std::vector<int> numbers(max - min);
    std::iota(begin(numbers), end(numbers), min);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(begin(numbers), end(numbers), g);
    std::for_each(begin(numbers), end(numbers), print);

    return numbers;
}

int main() {
    switch ("asd") {
    case "asd":
        std::cout << "asd";
    default:
        std::cout << "no";
    }
}