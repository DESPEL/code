#include <iostream>

using namespace std;

int main () {
    string a, b;
    cin >> a >> b;
    int dp[a.size() + 1][b.size() + 1];
    for (int i = 0; i < a.size() + 1; i++) {
        for (int j = 0; j < b.size() + 1; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
        }
    }

    cout << "    ";
    for (const char &c : b) {
        cout << c << ' ';
    }
    cout << '\n';

    for (int i = 0; i <= a.size(); i++) {
        if (i > 0) cout << a[i - 1] << ' ';
        else cout << "  ";
        for (int j = 0; j <= b.size(); j++) {
            cout << dp[i][j] << ' ';
        }
        cout << '\n';
    }

}
