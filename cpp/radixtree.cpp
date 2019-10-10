#include <iostream>
#include <vector>

using namespace std;

vector<bool> to_bits(string text) {
    vector<bool> res;
    for (char c : text) {
        for (int i = 0; i < 8; i++) {
            res.push_back((((char)(c << i) >> (7)) != 0));
        }
    }
    return res;
}

string to_string(vector<bool> bits) {
    string text;
    for (int i = 0; i < bits.size(); i += 8) {
        char l(0);
        for (int j = 7, pot = 1; j > 0; j--, pot *= 2) {
            l += pot * (bits[i + j]);
        }
        text += l;
    }
    return text;
}

struct Node {
    Node() {}
    Node(bool s) { set = true; }
    bool set = false;
    Node *lchild = nullptr;
    Node *rchild = nullptr;
};

class RadixTree {
    Node *root = new Node();

    void inorderH(Node *actual, vector<bool> &list) {
        if (actual == nullptr)
            return;
        list.push_back(false);
        inorderH(actual->lchild, list);
        list.pop_back();
        if (actual->set) {
            cout << to_string(list) << endl;
        }
        list.push_back(true);
        inorderH(actual->rchild, list);
        list.pop_back();
    }

    Node *findH(vector<bool> val) {
        Node *actual = root;
        for (bool v : val) {
            if (v) {
                if (actual->rchild == nullptr)
                    return nullptr;
                actual = actual->rchild;
            } else {
                if (actual->lchild == nullptr)
                    return nullptr;
                actual = actual->lchild;
            }
        }
        if (actual->set) {
            return actual;
        } else {
            return nullptr;
        }
    }

public:
    void insert(string text) { insert(to_bits(text)); }

    void insert(vector<bool> bits) {
        Node *actual = root;
        for (bool val : bits) {
            if (val) {
                if (actual->rchild == nullptr)
                    actual->rchild = new Node();
                actual = actual->rchild;
            } else {
                if (actual->lchild == nullptr)
                    actual->lchild = new Node();
                actual = actual->lchild;
            }
        }
        actual->set = true;
    }

    void inorder() {
        vector<bool> temp;
        inorderH(root, temp);
    }

    Node *find(string val) { return find(to_bits(val)); }
    Node *find(vector<bool> val) { return findH(val); }

    void remove(string val) { remove(to_bits(val)); }
    void remove(vector<bool> val) {
        Node *el = find(val);
        if (el == nullptr)
            return;
        el->set = false;
    }
};

int main() {
    cout << to_string(to_bits("AAA")) << endl;

    RadixTree p;
    p.insert("bbb");
    p.insert("ac");
    Node *a = p.find("ac");
    cout << a->set << endl;
    p.insert("aaab");
    p.inorder();
}