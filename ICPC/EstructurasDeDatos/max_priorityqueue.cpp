#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Element {
    int priority = 0;
    deque<int> *data = new deque<int>;
};

struct MaxPriorityQueue {
    vector<Element> data;

    int top() {
        return data[0].data -> front();
    }

    int getParent(int idx) {
        if (idx <= 0) return 0;
        if (idx % 2 == 1) return (idx - 1) / 2;
        else return (idx - 2) / 2;
    }

    void insert(int data, int priority = 0) {
        Element newEl;
        newEl.priority = priority;
        if (!find(priority)) newPriority(newEl);
        getData(priority) -> push_back(data);
    }

    void newPriority(Element item) {
        data.push_back(item);
        int idx = getParent(data.size() - 1);
        maxHeapify(idx);
    }

    void swap(int iidx, int fidx) {
        Element tempdata = data[iidx];
        data[iidx] = data[fidx];
        data[fidx] = tempdata;
    }

    void maxHeapify(int idx) {
        int lchild = 2 * idx + 1;
        int rchild = 2 * idx + 2;
        int maxval = idx;
        if (lchild < data.size() && data[lchild].priority > data[maxval].priority) {
            maxval = lchild;
        }
        if (rchild < data.size() && data[rchild].priority > data[maxval].priority) {
            maxval = rchild;
        }
        if (maxval != idx) {
            this -> swap(idx, maxval);
            maxHeapify(getParent(idx));
        }
    }

    bool find(int priority) {
        for (int i = 0; i < data.size(); i++) {
            if (data[i].priority == priority) return true;
        }
        return false;
    }

    deque<int> *getData(int priority) {
        for(int i = 0; i < data.size(); i++) {
            if (data[i].priority == priority) {
                return data[i].data;
            }
        }
    }

    void print() {

        for (int i = 0; i < data.size(); i++) {
            cout << data[i].priority << " -> ";
            deque<int>::iterator it = data[i].data -> begin();
            deque<int>::iterator it2 = data[i].data -> end();
            while(it != it2) {
                cout << *it << " ";
                it++;
            }
            cout << endl;
        }
    }
};

int main() {
    MaxPriorityQueue prueba;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 20; j++ ) {
            prueba.insert(i, j);
        }
    }
    prueba.print();
}
