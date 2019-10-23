#include <iostream>
#include <stack>

using namespace std;

char inverse(char a) {
    char b = (a == '{') ? '}' : (a == '[') ? ']' : (a == '(') ? ')' : '>';
    return b;
}

int main() {
    string s;
    cin >> s;
    stack<char> st;
    int bad = 0;
    for (char c : s) {
        if (c == '[' || c == '(' || c == '{' || c == '<')
            st.push(inverse(c));
        else if (st.empty()) {
            cout << "imposible";
            return 0;
        } else {
            bad += !(c == st.top());
            st.pop();
        }
    }
    cout << ((st.empty()) ? bad : "imposible");
    return 0;
}