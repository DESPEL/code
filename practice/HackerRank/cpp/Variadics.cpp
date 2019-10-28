// https://www.hackerrank.com/challenges/cpp-variadics/problem
#include <iostream>
#include <vector>

using namespace std;

template <bool ...bs>
class reversed_binary_value {
public:
    int value = 0;
    reversed_binary_value() {
        vector<bool> vals = {bs...};
        int val = 1;
        for (int i = 0; i < vals.size(); i++) {
            value += vals[i] * val;
            val *= 2;
        }
    }
    operator int() {
        return value;
    }
};



int main () {
    int c = reversed_binary_value<0,0,1>();
    cout << c;
}