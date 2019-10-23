#include <iostream>
#include <stack>

using namespace std;

int main() {
    string par;
    cin >> par;
    bool good = true;
    stack<char> st;
    for (char c : par) {
        if (c == '[' || c == '{' || c == '(') {
            st.emplace(c);
        } else {
            if (c == ']' && st.top() == '[') {
                st.pop();
            } else if (c == ')' && st.top() == '(') {
                st.pop();
            } else if (c == '}' && st.top() == '{') {
                st.pop();
            } else {
                good = false;
                break;
            }
        }
    }
    cout << (good ? "true" : "false");
}