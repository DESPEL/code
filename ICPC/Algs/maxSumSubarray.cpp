#include <bits/stdc++.h>

using namespace std;

struct maxData {
    int lidx;
    int ridx;
    int suma;
};

maxData computeMaxSubArr (int arr[], int inicio, int medio, int fin) {
    maxData data;
    int maxLSum = -2147483647;
    int suma = 0;
    int maxL;
    for (int i = medio; i >= inicio; i--) {
        suma += arr[i];
        if (suma > maxLSum) {
            maxLSum = suma;
            maxL = i;
        }
    }
    int maxRSum = -2147483647;
    int maxR;
    suma = 0;
    for (int i = medio + 1; i <= fin; i++) {
        suma += arr[i];
        if (suma > maxRSum) {
            maxRSum = arr[i];
            maxR = i;
        }
    }
    data.lidx = maxL;
    data.ridx = maxR;
    data.suma = maxLSum + maxRSum;
    return data;
}

maxData maxSubArr(int arr[], int inicio, int fin) {
    if (inicio == fin) {
        maxData data;
        data.lidx = inicio;
        data.ridx = fin;
        data.suma = arr[inicio];
        return data;
    }
    if (inicio < fin) {
        int med = (inicio + fin) / 2;
        maxData maxleft = maxSubArr(arr, inicio, med);
        maxData maxright = maxSubArr(arr, med + 1, fin);
        maxData maxcross = computeMaxSubArr(arr, inicio, med, fin);
        if (maxleft.suma >= maxright.suma && maxleft.suma >= maxcross.suma){
            return maxleft;
        } else if (maxright.suma >= maxleft.suma && maxright.suma >= maxcross.suma) {
            return maxright;
        } else {
            return maxcross;
        }
    }
}

void toDelta(int arr[], int sz) {
    int temparr[sz];
    for (int i = 0; i < sz; i++) {
        temparr[i] = arr[i];
    }
    for (int i = 1; i < sz; i++) {
        arr[i] = temparr[i] - temparr[i-1];
    }
    arr[0] = 0;
}

int main() {
    int arr[10] = {10, 20, 30, 40, -10};
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    maxData res = maxSubArr(arr, 0, 10);
    cout << endl;
    cout << res.lidx << " " << res.ridx << " " << res.suma << " ";
    return 0;
}
