#include <iostream>
#include <queue>

struct Node {
    Node() {}
    Node(int k, int d) {
        key = k;
        data = k;
    }
    int key;
    int data;
    Node *lchild = nullptr;
    Node *rchild = nullptr;
};

class BinaryTree {
    Node *head = NULL;

public:
    void insert(int key, int parent, int data) {
        Node *newChild = new Node(key, data);
        Node *nParent = find(parent);
    }

    Node *find(int val) {
        std::queue<Node *> cola;
        cola.push(head);
        while (!cola.empty()) {
            if (cola.front()->key == val) {
                return cola.front();
            }
            if (cola.front()->lchild != nullptr) {
                cola.push(cola.front->lchild);
            }
            if (cola.front()->rchild != nullptr) {
                cola.push(cola.front->rchild);
            }
            cola.pop();
        }
    }
};

int main() {
    int prueba[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    mostrarT(prueba);
};

void mostrarT(int tablero[8]) {}