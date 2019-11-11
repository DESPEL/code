// https://www.hackerrank.com/challenges/abbr/problem
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

bool canReduce(string a, string b, unordered_map<string, bool> &memo) {
    if (a.size() < b.size())
        return false;
    string key = a + ":" + b;
    if (memo.find(key) != end(memo))
        return memo[key];
    //cout << a.size() << ' ' << b.size() << '\n';
    if (a.empty() && b.empty()) {
        memo[key] = true;
        return true;
    }
    if (b.empty()) {
        if (a[a.size() - 1] == tolower(a[a.size() -1])) {
            a.pop_back();
            return canReduce(a, b, memo);
        }
        return false;
    }
    bool f1 = false;
    if (tolower(a[a.size() - 1]) == tolower(b[b.size() - 1])) {
        if (a[a.size() - 1] == tolower(a[a.size() - 1])) {
            //cout << 'a';
            a.pop_back();
            f1 = f1 || canReduce(a, b, memo);
        } else {
            a.pop_back();
        }
        //cout << 'b';
        b.pop_back();
        f1 = f1 || canReduce(a, b, memo);
    } else if (a[a.size() - 1] == tolower(a[a.size() - 1])) {
        //cout << 'c';
        a.pop_back();
        f1 = f1 || canReduce(a, b, memo);
    }
    memo[key] = f1;
    return f1;
}

int main () {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        unordered_map<string,bool> memo;
        string a, b;
        cin >> a >> b;
        if (canReduce(a,b, memo)) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }

}
