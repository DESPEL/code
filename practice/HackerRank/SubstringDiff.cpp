// https://www.hackerrank.com/challenges/substring-diff/problem
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int lcs(string a, string b, int k, unordered_map<string, int> &memo,int acc = 0) {
    string key = to_string(k) + ":" + a + ":" + b;
    if (memo.find(key) != end(memo))
        return memo[key];
    int maxn;
    if (a.size() == 0 || b.size() == 0)
        return acc;
    string c = a;
    string d = b;
    a.pop_back();
    b.pop_back();
    int t1, t2, t3;
    if (a[a.size() - 1] == b[b.size() - 1]) {
        t1 = lcs(a, b, k, memo, acc + 1);
    } else if (k > 0) {
        t1 = lcs(a, b, k - 1, memo, acc + 1);
    } else {
        t1 = lcs(a, b, k, memo, acc);
    }
    t2 = lcs(c, b, k, memo, acc);
    t3 = lcs(a, d, k, memo, acc);
    maxn = max(t1, max(t2, t3));
    memo[key] = maxn;
    return maxn;
}

int main () {
    int n;
    cin >> n;
    for (int i = 0;i < n; i++) {
        int k;
        string a, b;
        cin >> k >> a >> b;
        unordered_map<string, int> memo;
        cout << lcs(a, b, k, memo) << '\n';
    }
}
