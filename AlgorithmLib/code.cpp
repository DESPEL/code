#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

void printVector(vector<int>::iterator vectorStart, vector<int>::iterator vectorEnd) {
    while(vectorStart != vectorEnd) {
        cout << *vectorStart << " ";
        vectorStart++;
    }
    cout << endl;
    return;
}

void mostrar_ordenado(vector<int>::iterator in, vector<int>::iterator en) {
    bool sorted = is_sorted(in, en);
    cout << "Ordenado: " << (sorted ? "true" : "false") << endl;
    return;
}

int main() {
    srand((unsigned)time(NULL));
    vector<int> heaptest;
    int n = 10;
    for (int i = 0; i < n ; i++) {
        heaptest.push_back(rand() % 101);
    }
    make_heap(heaptest.begin(), heaptest.end());
    printVector(heaptest.begin(), heaptest.end());
    cout << endl;

    mostrar_ordenado(heaptest.begin(), heaptest.end());

    pop_heap(heaptest.begin(), heaptest.end());
    heaptest.pop_back();
    printVector(heaptest.begin(), heaptest.end());
    cout << endl;

    sort_heap(heaptest.begin(), heaptest.end());
    printVector(heaptest.begin(), heaptest.end());
    cout << endl;

    mostrar_ordenado(heaptest.begin(), heaptest.end());
}
