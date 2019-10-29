// https://www.hackerrank.com/challenges/string-reduction/problem
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int minsz(string s) {
    cout << s << '\n';
    if (s.size() == 2) {
        if (s[0] != s[1]) {
            return 1;
        } else {
            return 2;
        }
    }
    string temp = "";
    string s2 = s;
    s2.erase(begin(s2));
    int tsz;
    int min = numeric_limits<int>::max();
    bool changed = false;
    for (int i = 1; i < s.size(); i++) {
        s2.erase(begin(s2));
        if (temp.back() != s2.front()) {
            if (s[i - 1] != s[i]) {
                char t = 'a';
                if ((s[i - 1] == 'a' && s[i] == 'b') ||
                    (s[i] == 'a' && s[i - 1] == 'b'))
                    t = 'c';
                else if ((s[i - 1] == 'b' && s[i] == 'c') ||
                         (s[i] == 'b' && s[i - 1] == 'c'))
                    t = 'a';
                else if ((s[i - 1] == 'a' && s[i] == 'c') ||
                         (s[i] == 'a' && s[i - 1] == 'c'))
                    t = 'b';
                tsz = minsz(temp + t + s2);
                if (tsz < min) {
                    cout << tsz << '\n';
                    min = tsz;
                }
            }
            changed = true;
        }
        temp += s[i - 1];
    }
    if (!changed)
        return s.size();
    return min;
}

int strred(string &s) { return minsz(s); }

int main() {
    int t;
    cin >> t;
    string s;
    for (int i = 0; i < t; i++) {
        cin >> s;
        cout << strred(s) << '\n';
    }
}