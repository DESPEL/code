// https://www.hackerrank.com/challenges/stockmax/problem
#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>

using namespace std;

int stockMax(vector<int> &vals, int idx1 = 0, int idx2 = 0) {
    if (idx2 > idx1) return 0;
    if (idx1 >= vals.size() - 1) return 0;
    cout << "v: " << vals[idx2] - vals[idx1] << '\n';
    return max(
               (vals[idx1] - vals[idx2]) + stockMax(vals ,idx1 + 1, idx2 + 1),
               max((vals[idx1] - vals[idx2]) + stockMax(vals, idx1 + 1, idx2),
                   (vals[idx1] - vals[idx2]) + stockMax(vals, idx1, idx2 + 1))
               );
}

int main() {
    int t, n;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        vector<int> els(n);
        for (int j = 0; j < n; j++) {
            cin >> els[j];
        }
        cout << stockMax(els) << '\n';
    }
}
