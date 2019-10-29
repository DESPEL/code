// https://www.hackerrank.com/challenges/string-reduction/problem
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

pair<int, bool> minsz(string s) {
    if (s.size() == 2) {
        if (s[0] != s[1]) {
            return make_pair(1, true);
        } else {
            return make_pair(2, true);
        }
    }
    string temp = "";
    string s2 = s;
    s2.erase(begin(s2));
    pair<int, bool> tsz;
    int min = numeric_limits<int>::max();
    bool changed = false;
    for (int i = 1; i < s.size(); i++) {
        s2.erase(begin(s2));
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
            if (tsz.second == true) {
                return tsz;
            }
            if (tsz.first < min) {
                min = tsz.first;
            }

            changed = true;
        }
        temp += s[i - 1];
    }
    if (!changed)
        return make_pair(s.size(), false);
    return make_pair(min, false);
}

int strred(string &s) { return minsz(s).first; }

int main() {
    int t;
    cin >> t;
    string s;
    for (int i = 0; i < t; i++) {
        cin >> s;
        cout << strred(s) << '\n';
    }
}