#include <iostream>

using namespace std;

void mergeItems(int elementos[], int inicio, int medio, int fin) {

    int sz1 = medio - inicio + 1;
    int sz2 = fin - medio;
    int der[sz1];
    int izq[sz2];

    for (int i = 0; i < sz1; i++) {
        der[i] = elementos[inicio + i];
    }
    for (int i = 0; i < sz2; i++) {
        izq[i] = elementos[medio + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = inicio;
    while (i < sz1 && j < sz2) {
        if (der[i] < izq[j]) {
            elementos[k] = der[i];
            i++;
        } else {
            elementos[k] = izq[j];
            j++;
        }
        k++;
    }
    while (i < sz1) {
        elementos[k] = der[i];
        k++;
        i++;
    }
    while (j < sz2) {
        elementos[k] = izq[j];
        k++;
        j++;
    }
}

void mergeSort(int elementos[], int inicio, int fin) {
    int medio = (fin + inicio) / 2;
    if (inicio < fin) {
        mergeSort(elementos, inicio, medio);
        mergeSort(elementos, medio + 1, fin);
        mergeItems(elementos, inicio, medio, fin);
    }
}

int main() {
    int unsorted[] = {6,5,4,7,2,1};
    mergeSort(unsorted, 0, 6);
    for (int i = 0; i < 6; i++) {
        cout << unsorted[i] << " ";
    }
}
