#include <math.h>
#include <iostream>
#include <map>

using namespace std;

int pasos2[100000] = {-2};

void cantAlgoritmo(int &s, int &query, map<int, int> &index) {
    int indice = index[query];
    int pasos = 0;
    if (pasos2[indice] != -2) {
        cout << pasos << '\n';
        return;
    }
    if (indice == 0)
        pasos = -1;
    else if (indice % s == 0)
        pasos = indice / s;
    else {
        pasos += (indice / s) + 2;
        pasos += indice % s;
    }
    pasos2[indice] = pasos;
    cout << pasos << '\n';
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;
    map<int, int> index;
    // index.rehash(n);
    int temp;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        index[temp] = i + 1;
    }
    n = sqrt(n);

    for (int i = 0; i < q; i++) {
        cin >> temp;
        cantAlgoritmo(n, temp, index);
    }

    return 0;
}