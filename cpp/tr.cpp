#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long int q;
    cin >> q;
    for (long long int _i = 0; _i < q; ++_i) {
        bool completado = false;
        long long int n, m;
        cin >> n >> m;
        vector<long long int> valores;
        for (long long int i = 0; i < n; ++i) {
            long long int temp;
            cin >> temp;
            if (temp % m == n - 1) {
                completado = true;
            }
            valores.push_back(temp % m);
        }
        if (completado) {
            cout << n - 1 << '\n';
            continue;
        }

        vector<vector<long long int>> subsum(n, vector<long long int>());
        subsum[0] = valores;
        long long int max = 0;
        for (long long int i = 1; i < n; i++) {
            for (long long int j = 0; j < n - i; j++) {
                subsum[i].push_back((subsum[i - 1][j] + subsum[i - 1][j + 1]) %
                                    m);
                if (subsum[i][j] > max) {
                    max = subsum[i][j];
                    if (max == n - 1) {
                        goto romper;
                    }
                }
            }
        }
    romper:
        cout << max << '\n';
    }
}
