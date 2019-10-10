#include <bits/stdc++.h>

using namespace std;

int rightChild(int idx) {
    return 2 * idx + 2;
}

int leftChild(int idx) {
    return 2 * idx + 1;
}

int parent(int idx) {
    if (idx == 0) return 0;
    if (idx %2 == 1) {
        return (idx - 1) / 2;
    } else {
        return (idx - 2) / 2;
    }
}

bool hasRightChild(vector<int> *heap, int idx) {
    if (rightChild(idx) >= heap -> size()) {
        return false;
    }
    return true;
}

bool hasLeftChild(vector<int> *heap, int idx) {
    if (leftChild(idx) >= heap -> size()) {
        return false;
    }
    return true;
}

void swapElements(vector<int> *heap, int sidx, int fidx) {
    int temp = (*heap)[sidx];
    (*heap)[sidx] = (*heap)[fidx];
    (*heap)[fidx] = temp;
}

void maxHeapify(vector<int> *heap, int pos) {
    int heapmax = pos;
    if (hasRightChild(heap, pos) && (*heap)[rightChild(pos)] > (*heap)[heapmax]) {
        heapmax = rightChild(pos);
    }
    if (hasLeftChild(heap, pos) && (*heap)[leftChild(pos)] > (*heap)[heapmax]) {
        heapmax = leftChild(pos);
    }
    if (heapmax != pos) {
        swapElements(heap, pos, heapmax);
        maxHeapify(heap, parent(pos));
    }
}

void reHeap(vector<int> *heap, int pos) {
    int heapmax = pos;
    if (hasRightChild(heap, pos) && (*heap)[rightChild(pos)] > (*heap)[heapmax]) {
        heapmax = rightChild(pos);
    }
    if (hasLeftChild(heap, pos) && (*heap)[leftChild(pos)] > (*heap)[heapmax]) {
        heapmax = leftChild(pos);
    }
    if (heapmax != pos) {
        swapElements(heap, pos, heapmax);
        reHeap(heap, heapmax);
    }
}

void heapInsert(vector<int> *heap, int data) {
    int par = heap -> size();
    (*heap).push_back(data);
    maxHeapify(heap, parent(par));
}

int heapPop(vector<int> *heap) {
    int value = (*heap)[0];
    (*heap)[0] = (*heap)[heap -> size() - 1];
    heap -> pop_back();
    reHeap(heap, 0);
    return value;
}

void heapSort(vector<int> *heap) {
    vector<int> sorted;
    while(!heap -> empty()) {
        sorted.push_back(heapPop(heap));
    }
    for (int i = 0; i < sorted.size(); i++) {
        heap -> push_back(sorted[i]);
    }
}

int main() {
    vector<int> heap;
    int n, val;
    cin >> n;
    for (int i = 0; i < n; i++) {
        heapInsert(&heap, i);
    }
    cout << heap.size() << endl;
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
    heapSort(&heap);
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }
    cout << endl;

}
