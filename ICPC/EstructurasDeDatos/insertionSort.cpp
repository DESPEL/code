#include <iostream>

using namespace std;

void intInsertionSort(int element[], int sz) {
    int temp;
    for (int i = 0; i < sz; i++) {
        if (i == 0) continue;
        if (element[i] < element[i - 1]) {
            temp = element[i];
            element[i] = element[i - 1];
            element[i - 1] = temp;
            i -= 2;
        }
    }
}

int main() {
    int sz = 6;
    int elements[sz] = {5,4,3,2,1,6};
    intInsertionSort(elements, sz);
    for (int i = 0; i < 6; i++) {
        cout << elements[i] << " ";
    }
}
