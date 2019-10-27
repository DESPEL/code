#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct cuarto {
    vector<int> a;
};

int main () {
    int n, c;
    cin >> n >> c;
    int n1, n2;
    
    vector<cuarto> cuartos(n);
    vector<bool> vis(n, false);
    for (int i = 0; i < n - 1; i++) {
        cin >> n1 >> n2;
        cuartos[n1 - 1].a.push_back(n2 - 1);
        cuartos[n2 - 1].a.push_back(n1- 1);
    }
    int guardias = 0;
    int i = 0;
    for (cuarto &c : cuartos) {
        if (vis[i]) {
            i++;
            continue;
        }
        vis[i] = true;
        bool visited = false;
        for (int &pos : c.a) {
            if (vis[pos])
                visited = true;
            else 
                vis[pos] = true;
        }
        if (!visited)
            guardias++; 
        i++;
    }
    cout << guardias * c << '\n';
}