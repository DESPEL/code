#include <iostream>

using namespace std;

struct Node() {
    Node() {}
    Node(bool s) { set = true; }
    bool set = false;
    Node *lchild = nullptr;
    Node *rchild = nullptr;
}

class RadixTree {
    Node *root = new Node();

public:
}

int main () {
}