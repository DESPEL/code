#include <iostream>

using namespace std;

template <typename T>
struct Node {
    Node() {}
    Node(T d) { data = d; }
    T data;
    Node<T> *lchild = nullptr;
    Node<T> *rchild = nullptr;
};

template <typename T>
class BST {
    Node<T> *head = nullptr;

    void insertHelper(Node<T> *actual, Node<T> *newNode) {
        if (actual->data > newNode->data) {
            if (actual->lchild == nullptr) {
                actual->lchild = newNode;
                return;
            }
            insertHelper(actual->lchild, newNode);
        } else {
            if (actual->rchild == nullptr) {
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

    Node<T> *searchH(Node<T> *actual, T &val) {
        if (actual == nullptr || actual->data == val)
            return actual;
        if (val < actual->data)
            return searchH(actual->lchild, val);
        else
            return searchH(actual->rchild, val);
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

    void preorder() { preorderH(head); }

    void inorder() { inorderH(head); }

    void outorder() { outorderH(head); }

    void postorder() { postorderH(head); }

    bool recfind(T val) {
        if (searchH(head, val) == nullptr) {
            return false;
        }
        return true;
    }

    bool find(T val) {
        Node<T> *actual = head;
        while (actual != nullptr) {
            if (actual->data == val)
                return true;
            if (val < actual->data)
                actual = actual->lchild;
            else
                actual = actual->rchild;
        }
        return false;
    }
};

int main() {
    BST<int> a;
    a.insert(5);
    a.insert(4);
    a.insert(3);
    a.insert(8);
    a.insert(6);
    a.insert(9);
    cout << a.find(6);
}

/// asdfasd