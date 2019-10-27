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
    char simbolo;
    while (idx < coso.size() && coso[idx] != '*' && coso[idx] != '+') idx++;
    cout << idx;
    if (idx == coso.size() - 1) {
        return make_pair(coso, ' ');
    }
    simbolo = coso[idx];
    while (coso[idx] != ' ') idx++;
    for (; idx < coso.size() - 1; idx++) {
        if (coso[idx] == ' ')
            continue;
        if (coso[idx] == '(') {
            pair<string, char> tempres = conversor(coso, idx);

            if (simbolo == '*' && tempres.second == '+') {
                res += "(" + tempres.first + ")";
            } else {
                if (tempres.second == simbolo) res += simbolo;
                res += tempres.first;
            }
            continue;
        }
        

        if (coso[idx] == ')') {
            idx++;
            return make_pair(res, simbolo);
        } else {
            res += coso[idx];
        }
        if (coso[idx + 1] != ')')
            res += simbolo;

        
        cout << coso[idx] << simbolo << endl;
    }

    return make_pair(res, simbolo);
}
/// a + b * c
// c = (d + e + f)

int main() {
    string op;
    cin.ignore();
    getline(cin, op);

    vector<char> stack;
    vector<char> resultado;
    int idx = 0;
    cout << conversor(op, idx).first;
}