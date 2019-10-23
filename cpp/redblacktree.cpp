#include <iostream>

#define red = false
#define black = true

using namespace std;

template <typename T>
struct Node {
    Node() {}
    Node(T d) { data = d; }
    T data;
    bool color = black;
    Node *parent = nullptr;
    Node *lchild = nullptr;
    Node *rchild = nullptr;
};

template <typename T>
class RedBlackTree {
    Node<T> *root = nullptr;

    void left_rotate(Node<T> *x) {
        Node<T> *y = x->rchild;
        x->rchild = y->lchild;
        y->lchild = x;
        if (y->lchild != nullptr) {
            y->lchild->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void right_rotate(Node<T> *x) {
        Node<T> *y = x->lchild;
        x->lchild = y->rchild;
        y->rchild = x;
        if (y->rchild != nullptr)
            y->rchild->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
    }

public:
    void insert(T element) {
        Node<T> *newNode = new Node(element);
        Node<T> *actual = root;
        Node<T> *parent = nullptr;
        while (actual != nullptr) {
            parent = actual;
            if (element < actual->data) {
                actual = actual->lchild;
            } else {
                actual = actual->rchild;
            }
        }
        newNode->parent = parent;
        actual = newNode;
        actual->color = red;
        insert_fix(actual);
    }

    void insert_fix(Node<T> *inserted) {
        while (inserted->parent->color == red) {
            if (inserted->parent == inserted->parent->parent->lchild) {
                Node<T> *y = inserted->parent->parent->rchild;
                if (y->color == red) {
                    inserted->parent->color = black;
                    y->color = black;
                    inserted->parent->parent->color = red;
                    inserted = inserted->parent->parent;
                } else {
                    if (inserted == inserted->parent->rchild) {
                        inserted = inserted->parent;
                        left_rotate(inserted->parent->parent);
                    }
                    inserted->parent->color = black;
                    inserted->parent->parent->color = red;
                    right_rotate(inserted->parent->parent);
                }
            } else {
                Node<T> *y = inserted->parent->parent->lchild;
                if (y->color == red) {
                    inserted->parent->color = black;
                    y->color = black;
                    inserted->parent->parent->color = red;
                    inserted = inserted->parent->parent;
                } else {
                    if (inserted == inserted->parent->lchild) {
                        inserted = inserted->parent;
                        right_rotate(inserted->parent->parent);
                    }
                    inserted->parent->color = black;
                    inserted->parent->parent->color = red;
                    left_rotate(inserted->parent->parent);
                }
            }
        }
    }
};

int main() { sort() }