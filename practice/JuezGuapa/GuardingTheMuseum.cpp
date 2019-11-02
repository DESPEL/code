// https://www.juezguapa.com/problemas/enunciado/guarding-the-museum
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct node {
    bool guard = false;
    int idx = 0;
    int prot = 0;
    int degree = 1;
    node *parent = nullptr;
    vector<node *> childs;
};

node *getRoot(vector<node *> &tree) {
    node *actual = tree[0];
    while (actual->parent != nullptr) actual = actual->parent;
    return actual;
}

int nguards(vector<node *> &museo, int idx = 0) {
    /// treeify?, idk bfs

    int guards = 0;
    if (museo.size() == 1)
        return 1;
    stack<node *> pila;
    stack<node *> pila2;
    node *root = museo[0];  // getRoot(museo);
    root -> parent = nullptr;
    pila.push(root);
    pila2.push(root);
    while (!pila2.empty()) {
        node *actual = pila2.top();
        pila2.pop();
        for (int i = 0; i < actual->childs.size(); i++) {
            if (actual->childs[i] == nullptr)
                continue;
            if (actual->parent != nullptr && actual->childs[i] == actual->parent) {
                actual->childs[i] = nullptr;
                continue;
            }
            actual->degree++;
            actual->childs[i]->parent = actual;
            pila.push(actual->childs[i]);
            pila2.push(actual->childs[i]);
        }
        if (actual -> parent == nullptr)
            actual->degree--;
    }
    node *actual;
    while (!pila.empty()) {
        actual = pila.top();
        cout << "it " << actual->degree << " " << actual->idx + 1 << '\n';
        pila.pop();
        
        if (actual->degree == 1 || actual -> parent == nullptr)
            continue;
        
        cout << "a";
        if (actual->degree == 2 && actual->prot == 0 &&
            actual->childs[0]->prot == 0) {
            guards++;
            actual->parent->prot++;
            actual->prot++;
            actual->guard = true;
        }
        if (actual->degree > 2 && actual->prot < actual->degree - 1 &&
            actual->parent != nullptr) {
            guards++;
            actual->parent->prot++;
            actual->prot++;
            actual->guard = true;
        }
    }
    if (!actual->prot) {
        actual->guard = true;
        guards++;
    }
    return guards;
}

int main() {
    int n, p1, p2, c;
    cin >> n >> c;
    vector<node *> museo(n, nullptr);
    for (int i = 0; i < n - 1; ++i) {
        cin >> p1 >> p2;
        if (museo[p1 - 1] == nullptr)
            museo[p1 - 1] = new node();
        if (museo[p2 - 1] == nullptr)
            museo[p2 - 1] = new node();
        museo[p2 - 1]->childs.push_back(museo[p1 - 1]);
        museo[p2 - 1]->idx = p2 - 1;
        museo[p1 - 1]->childs.push_back(museo[p2 - 1]);
        museo[p1 - 1]->idx = p1 - 1;
        //museo[p2 - 1]->degree++;
        //museo[p1 - 1]->degree++;
    }

    cout << nguards(museo) * c << '\n';
     for (node *c : museo) {
        cout << "a";
    }
    // for (int i = 0; i < n; i++) {
    //    cout << "nodo:" << i + 1 << " " << museo[i]->guard << " "
    //         << museo[i]->degree << '\n';
    //}

    return 0;
}