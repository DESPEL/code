#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k, ndulces;
    cin >> n >> k;
    queue <int> nums;
    int maxdul = 0;
    int suma = 0;
    for (int i = 0; i < n; i++) {
        cin >> ndulces;
        nums.push(ndulces);
        suma += ndulces;
        if (i >= k) {
            suma -= nums.front();
            nums.pop();
        }
        if (suma > maxdul) maxdul = suma;
    }
    cout << maxdul;
}
