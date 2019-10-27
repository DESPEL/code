#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
    node () {
        childs.resize(26);
    }
    bool def = false;
    vector<node*> childs;
};

struct radixtree {
    node* root = new  node();
    int max = 0;
    
    void insert(string &s) {
        //bool lasttrue = false;
        node* actual = root;
        for (char &c : s) {
            //lasttrue = false;
            int indice = 'z' - c;
            if (actual->childs[indice] == nullptr) {
                actual->childs[indice] = new node();
                //lasttrue = true;
            }
            if (actual->def) {
                actual->def = false;
                --max;
            }
            actual = actual->childs[indice];
        }
        //if (lasttrue) --max;
        ++max;
        actual->def = true;
    }
};

int main() {
    
    vector<string> palabras;
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        string temp;
        cin >> temp;
        palabras.push_back(temp);
    }

    sort(palabras.begin(), palabras.end());     
    radixtree pref;
    string last = "";
    for(string &palabra: palabras) {
        if (palabra == last) continue;
        pref.insert(palabra);
        last = palabra;
    }   
    cout << pref.max << '\n';

    return 0;
}