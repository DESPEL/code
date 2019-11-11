#include <iostream>

using namespace std;

int lcs(string &s1, string &s2, int i, int j, int **memo) {
    if (i < 0 || j < 0)
        return 0;
    if (memo[i][j] != 0)
        return memo[i][j];

    if (s1[i] == s2[j]) {
        memo[i][j] = 1 + lcs(s1, s2, i -1, j - 1, memo);
    } else {
        memo[i][j] = max(
                         lcs(s1, s2, i - 1, j, memo),
                         lcs(s1, s2, i, j - 1, memo)
                         );
    }
    return memo[i][j];
}

int main () {
    string s1, s2;
    cin >> s1 >> s2;

    int **memo = new int*[s1.size()];
    for (int i = 0; i < s1.size(); i++) {
        memo[i] = new int[s2.size()];
        for (int j = 0; j < s2.size(); j++)
            memo[i][j] = 0;
    }
    lcs(s1, s2, s1.size() -1, s2.size() - 1, memo);
    cout << "  ";
    for (int i = 0; i < s2.size(); i++) {
        cout << s2[i] << ' ';
    }
    cout << '\n';
    for (int i = 0; i < s1.size(); i++) {
        cout << s1[i] << ' ';
        for (int j = 0; j < s2.size(); j++)
            cout << memo[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}
