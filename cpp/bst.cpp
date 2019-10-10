#include <iostream>

using namespace std;

template <typename T>
struct Node {
    Node() {}
    Node(T d) { data = d; }
    T data;
    Node<T> *parent = nullptr;
    Node<T> *lchild = nullptr;
    Node<T> *rchild = nullptr;
};

template <typename T>
class BST {
    Node<T> *head = nullptr;

    void insertHelper(Node<T> *actual, Node<T> *newNode) {
        if (actual->data > newNode->data) {
            if (actual->lchild == nullptr) {
                newNode->parent = actual;
                actual->lchild = newNode;
                return;
            }
            insertHelper(actual->lchild, newNode);
        } else {
            if (actual->rchild == nullptr) {
                newNode->parent = actual;
                actual->rchild = newNode;
                return;
            }
            insertHelper(actual->rchild, newNode);
        }
    }

    void preorderH(Node<T> *actual) {
        if (actual == nullptr)
            return;
        cout << actual->data << endl;
        inorderH(actual->lchild);
        inorderH(actual->rchild);
    }

    void inorderH(Node<T> *actual) {
        if (actual == nullptr)
            return;
        inorderH(actual->lchild);
        cout << actual->data << endl;
        inorderH(actual->rchild);
    }

    void outorderH(Node<T> *actual) {
        if (actual == nullptr)
            return;
        outorderH(actual->rchild);
        cout << actual->data << endl;
        outorderH(actual->lchild);
    }

    void postorderH(Node<T> *actual) {
        if (actual == nullptr)
            return;
        postorderH(actual->lchild);
        postorderH(actual->rchild);
        cout << actual->data << endl;
    }

    Node<T> *recsearch(Node<T> *actual, T &val) {
        if (actual == nullptr || actual->data == val)
            return actual;
        if (val < actual->data)
            return searchH(actual->lchild, val);
        else
            return searchH(actual->rchild, val);
    }

    Node<T> *minimum(Node<T> *actual) {
        while (actual->lchild != nullptr) actual = actual->lchild;
        return actual;
    }

    Node<T> *maximum(Node<T> *actual) {
        while (actual->rchild != nullptr) actual = actual->rchild;
        return actual;
    }

    void transplant(Node<T> *u, Node<T> *v) {
        if (u->parent == nullptr) {
            head = v;
        } else if (u == u->parent->lchild) {
            u->parent->lchild = v;
        } else {
            u->parent->rchild = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

public:
    void insert(int data) {
        if (head == nullptr) {
            head = new Node<T>(data);
            return;
        }
        Node<T> *actual = head;
        Node<T> *newNode = new Node<T>(data);
        insertHelper(actual, newNode);
    }

    void remove(Node<T> *node) {
        if (node->lchild == nullptr) {
            Node<T> *rchild = node->rchild;
            delete node;
            node = rchild;
            return;
        }
        if (node->rchild == nullptr) {
            Node<T> *lchild = node->lchild;
            delete node;
            node = lchild;
            return;
        }
        Node<T> *succsr = successor(node);
        if (node != succsr->parent) {
            transplant(succsr, succsr->rchild);
            succsr->rchild = node->rchild;
            succsr->rchild->parent = succsr;
        }
        transplant(node, succsr);
        succsr->lchild = node->lchild;
        succsr->lchild->parent = succsr;
        delete node;
    }

    void preorder() { preorderH(head); }

    void inorder() { inorderH(head); }

    void outorder() { outorderH(head); }

    void postorder() { postorderH(head); }

    Node<T> *search(T &val) {
        Node<T> *actual = head;
        while (actual != nullptr && actual->data != val) {
            if (val < actual->data)
                actual = actual->lchild;
            else
                actual = actual->rchild;
        }
        return actual;
    }

    Node<T> *successor(Node<T> *actual) {
        if (actual->rchild != nullptr)
            return minimum(actual->rchild);
        Node<T> *next = actual->parent;
        while (next != nullptr && next->rchild == actual) {
            actual = next;
            next = next->parent;
        }
        return next;
    }

    Node<T> *predecessor(Node<T> *actual) {
        if (actual->lchild != nullptr)
            return maximum(actual->lchild);
        Node<T> *next = actual->parent;
        while (next != nullptr && next->lchild == actual) {
            actual = next;
            next = next->parent;
        }
        return next;
    }

    bool recfind(T val) {
        if (searchH(head, val) == nullptr) {
            return false;
        }
        return true;
    }

    bool find(T val) {
        if (search(val) == nullptr) {
            return false;
        }
        return true;
    }

    T min() { return minimum(head)->data; }

    T max() { return maximum(head)->data; }
};

int main() {
    BST<int> a;
    a.insert(5);
    a.insert(4);
    a.insert(3);
    a.insert(8);
    a.insert(6);
    a.insert(9);
    a.inorder();
    int b = 8;
    a.remove(a.search(b));
    cout << endl;
    b = 5;
    a.remove(a.search(b));
    a.inorder();
}