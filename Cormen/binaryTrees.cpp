#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int contarPares(vector<int> els) {
    int res = 0;
    unordered_map<int, int> p;
    for (int el : els) {
        p[el]++;
    }
    unordered_map<int, int>::iterator a = p.begin();
    while (a != p.end()) {
        res += a->second / 2;
        a++;
    }

    return res;
}

int divisorSum(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0)
            sum += i;
    }
    return sum;
}

int main() {
    vector<int> a({1, 1, 2, 2, 3, 3, 4, 4, 5});
    cout << contarPares(a);
}