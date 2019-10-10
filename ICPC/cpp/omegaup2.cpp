#include <bits/stdc++.h>

using namespace std;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    __int128 numero;
    __int128 repeticiones;
    int veces;
    cin >> veces;
    __int128_t int res = 0;
    for (int i = 0; i < veces; i++) {
        cin >> numero >> repeticiones;
        do {
            res = 0;
            while (numero >= 1) {
                res += numero % 10;
                numero /= 10;
            }

            if (repeticiones > 1) {
                res *= repeticiones;
                repeticiones = 1;
            }
            numero = res;
        } while (res >= 10);
        cout << res << "\n";
    }
}
