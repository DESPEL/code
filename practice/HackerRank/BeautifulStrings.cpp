// https://www.hackerrank.com/challenges/beautiful-string/problem
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int nstrings(string s) {
    string base;
    string s2 = s;
    s2.erase(begin(s2));
    for (int i = 0; i < s.size(); i++) {
        for (int j = i; j < s.size(); j++) {
            
        }
    }
}

int beautifulstring(string s) {
    return nstrings(s);
}

int main () {
    string s;
    cin >> s;
}