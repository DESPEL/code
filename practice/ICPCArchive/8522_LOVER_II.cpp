// https://icpcarchive.ecs.baylor.edu/external/85/8522.pdf
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    for (int z = 0; z < t; z++) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> muj(n);
        vector<int> hom(m);
        for (int i = 0; i < n; ++i)
            cin >> muj[i];
        for (int i = 0; i < m; ++i)
            cin >> hom[i];
        if (m < n) {
            cout << "0" << '\n';
            continue;
        }
        sort(begin(hom), end(hom), [] (int &a, int &b) {return a > b;});
        sort(begin(muj), end(muj));
        bool good = true;
        for (int i = muj.size() - 1; i >= 0; i--) {
            if (hom[i] + muj[i] < k) {
                good = false;
                cout << "0" << '\n';
                break;
            }
        }
        if (good) {
            cout << "1" << '\n';
        }
    }
    return 0;
}