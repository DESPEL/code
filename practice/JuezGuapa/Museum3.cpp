#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct node {
    int prot = 0;
    int idx = 0;
    node *parent = nullptr;
    vector<node *> childs;
};

int main () {
    int n, c, t1, t2;
    cin >> n >> c;
    vector<node *> museum(n, nullptr);
    for (int i = 0; i < n - 1; i++){
        cin >> t1 >> t2;
        if (museum[t1 - 1] == nullptr)
            museum[t1 - 1] = new node();
        if (museum[t2 - 1] == nullptr)
            museum[t2 - 1] = new node();
        museum[t1 - 1]->childs.push_back(museum[t2 - 1]);
        museum[t1 - 1]->idx = t1 - 1;
        museum[t2 - 1]->childs.push_back(museum[t1 - 1]);
        museum[t2 - 1]->idx = t2 - 1;
    }
    int bad = 0;
    int good = 0;
    stack<node *> s;
    stack<node *> s2;
    s.push(museum[0]);
    s2.push(museum[0]);
    int guards = 0;
    while (!s2.empty()) {
        node *actual = s2.top();
        cout << actual << '\n';
        cout << "sz: " << actual->childs.size() << '\n';
        s2.pop();
        //if (actual->childs.size() == 0) {
        //    if (actual->parent != nullptr) {
        //        actual->parent->prot = 0;
        //        good++;
        //    }
        //}
        for (int i = 0; i < actual->childs.size(); i++) {
            if (actual->parent != nullptr && actual->childs[i]->parent == actual->parent) {
                actual->childs[i] = actual->childs[actual->childs.size() - 1];
                actual->childs.resize(actual->childs.size() - 1);
                if (actual->childs.size() == 0)
                    continue;
            }
            actual->childs[i]->parent = actual;
            s2.push(actual->childs[i]);
            s.push(actual->childs[i]);
        }
    }

    cout << guards * c << '\n';
}
