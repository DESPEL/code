#include <iostream>

using namespace std;

int max10(int x) {
    int r = 0;
    while (r < x)
        r*=10;
    return r;
}

bool isPalindrome(int x) {
    if (x < 0) return false;
    if (x < 10) return true;
    int it = 0;
    while (x > 0) {
        if (x < 10) return true;
        if (x / max10(x) * (x % 10) > 1)
            return false;
        x %= max10(x);
        x /= 10;
        cout << x << '\n';
    }
    cout << it << '\n';
    return true;
}

int main() {
    isPalindrome(100);
    return 0;
}
