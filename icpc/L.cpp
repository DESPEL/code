#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct operador {
    char op;
    char par;
};

pair<string, char> conversor(string &coso, int &idx) {
    string res = "";
    if (coso[idx] == '(') idx++;
    char simbolo = coso[idx];
    if (!(simbolo == '+' || simbolo == '*')) {
        return make_pair(coso, ' ');
    }
    idx++;
    for (; idx < coso.size() - 1; idx++) {
        if (coso[idx] == '(') {
            idx++;
            pair<string, char> tempres = conversor(coso, idx);
            if (simbolo == '*' && tempres.second == '+') {
                res += "(" + tempres.first + ")";
            } else {
                res += tempres.first;
            }
            if (coso[idx] != ')') {
                res += simbolo;
            }
        }
        if (coso[idx] == ' ') {
            continue;
        }
        if (coso[idx] == ')') {
            idx++;
            return make_pair(res, simbolo);
        }
        if (coso[idx + 1] != ')') {
            res += coso[idx];
            res += simbolo;
        } else {
            res += coso[idx];
        }
    }

    return make_pair(res, simbolo);
}

int main() {
    string op;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin.ignore();
        getline(cin, op);
        int idx = 0;
        cout << conversor(op, idx).first << '\n';
    }
    return 0;
}