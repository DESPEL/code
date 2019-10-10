#include <bits/stdc++.h>


// O(2^n) solution
int findMax(std::map<int,int> &prices, int sz) {
    if (sz == 0) return 0;

    int maxv = -2147483647;
    for (int i = 0; i < sz; i++) {
        maxv = std::max(maxv, prices[i] + findMax(prices, sz - i));
    }

    return maxv;
}

// DP Memoization
int findMaxMemoized(int aux[], std::map<int,int> prices, int sz) {
    if(aux[sz] >= 0) return aux[sz];
    if (sz == 0) {
        aux[sz] = 0;
        return 0;
    }
    int maxv = -2147483647;
    for (int i = 0; i < sz; i++) {
        maxv = std::max(maxv, prices[i] + findMaxMemoized(aux, prices, sz - i));
    }
    aux[sz] = maxv;
    return maxv;
}

int findMaxMem(std::map<int,int> &prices, int sz) {
    int aux[sz + 1] = {-2147483647};
    return findMaxMemoized(aux, prices, sz);
}

// DP Bottom-Up

int findMaxBU(std::map<int,int> &prices, int sz) {
    int aux[sz + 1];
    aux[0] = 0;
    int maxv;
    for (int j = 1; j <= sz; j++ ) {
        maxv = -2147483647;
        for (int i = 0; i < j; i++) {
            maxv = std::max(maxv, prices[i] + aux[j - i]);
        }
        aux[j] = maxv;
    }

    return aux[sz];
}

int main() {
}
