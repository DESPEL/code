// https://www.codewars.com/kata/strip-comments/javascript
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
istream &operator>>(istream &in, vector<T> container) {
    T temp;
    for (int i = 0; i < container.size(); i++) {
        cin >> temp;
        container[i] = temp;
    }
    cout << "container: ";
    for (T c : container) {
        cout << c << " ";
    }
    return in;
}

void printstr(string texto) {
    char last;
    for (char c : texto) {
        if (c != '\\') {
            cout << c;
        }
        if (last == '\\' && c == 'n') {
            cout << endl;
        }
        last = c;
    }
}

int main() {
    string texto;
    getline(cin, texto);

    int n;
    cin >> n;
    vector<char> comments(n);
    cin >> comments;

    string textofinal = "";
    char prev;
    bool comentario = false;
    for (char c : texto) {
        for (char comm : comments) {
            cout << comm << endl;
            if (c == comm) {
                comentario = true;
            }
        }
        if (prev == '\\' && c == 'n') {
            comentario = false;
        }
        if (!comentario) {
            textofinal += string(1, c);
        }
        prev = c;
    }
    cout << textofinal << endl;
    printstr(textofinal);
}