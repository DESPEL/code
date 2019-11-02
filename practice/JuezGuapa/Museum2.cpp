#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct node {
    int prot = 0;
    int idx = 0;
    node *parent = nullptr;
    vector<node *> siblings;
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
        museum[t1 - 1]->siblings.push_back(museum[t2 - 1]);
        museum[t1 - 1]->idx = t1;
        museum[t2 - 1]->siblings.push_back(museum[t1 - 1]);
        museum[t2 - 1]->idx = t2;
    }
    // dfs
    bool vis[n] = {false};
    stack<node *> s;
    stack<node *> s2;
    s.push(museum[0]);
    s2.push(museum[0]);
    int guards = 0;
    while (!s2.empty()) {
        bool par = false;
        node *actual = s2.top();
        //cout << "rev: " << actual->idx << '\n';
        s2.pop();
        for (int i = 0; i < actual->siblings.size(); i++) {
            if (actual->parent != nullptr) {
                if(actual->parent == actual->siblings[i]) {
                    actual->siblings[i] = actual->siblings[actual->siblings.size() - 1];
                    par = true;
                    continue;
                } else if(!vis[actual->siblings[i]->idx - 1]) {
                    actual->siblings[i]->parent = actual;
                    s.push(actual->siblings[i]);
                    s2.push(actual->siblings[i]);
                    vis[actual->siblings[i]->idx - 1] = true;
                }
            } else if(!vis[actual->siblings[i]->idx - 1]) {
                actual->siblings[i]->parent = actual;
                s.push(actual->siblings[i]);
                s2.push(actual->siblings[i]);
                vis[actual->siblings[i]->idx - 1] = true;
            }
        }
        if (par) {
            actual->siblings.resize(actual->siblings.size() - 1);
        }
    }
    // reverse dfs
    //cout << "sz: " << s.size() << '\n';
    node* actual;
    while(!s.empty()){
        actual = s.top();
        s.pop();
        //cout << "idx: " << actual->idx << " sz: " << actual->siblings.size() << '\n';
        if (actual->siblings.size() == 0 || actual->parent == nullptr) {
            continue;
        }
        if (actual->siblings.size() == 1) {
            if (actual->prot == 0) {
                actual->prot++;
                actual->parent->prot++;
                guards++;
                //cout << "guard at: " << actual->idx << '\n';
            }
        } else { // childs a.k.a siblings > 2
            if (actual->prot < actual->siblings.size()) {
                actual->prot = actual->siblings.size();
                actual->parent->prot++;
                guards++;
                //cout << "guard at: " << actual->idx << '\n';
            }
        }
    }
    if (actual->prot == 0) {
        //cout << "guard at: " << actual->idx << '\n';
        guards++;
    }

    cout << guards * c << '\n';
}
