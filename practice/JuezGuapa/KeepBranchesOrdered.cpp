// https://www.juezguapa.com/problemas/enunciado/keep-branches-ordered

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool ciudad[100][100] = {{false}};
int valores[100] = {0};
bool visited[100] = {false};

struct step {
    step() {}
    step(int idx, int dis) {
        i = idx;
        d = dis;
    }
    int i;
    int d;
};


int main() {
    bool cycle = false;
    int sz;
    cin >> sz;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            cin >> ciudad[i][j];
            if (ciudad[j][i] && ciudad[i][j]) {
                // cout << j << " " <<  i;
                cycle = true;
            }
        }
    }
    if (cycle) {
        cout << -1 << '\n';
        return 0;
    }
    auto compare = [](const step &a, const step &b) {
        return a.d > b.d;
    };
    for (int i = 0; i < sz; i++) {
        if (valores[i] != 0)
            continue;
        //cout << i + 1 << '\n';
        // bad bfs;
        priority_queue<step, vector<step>, decltype(compare)> cola(compare);
        cola.emplace(i, 1);
        bool vis[100] = {false};
        valores[i] = 1;
        vis[i] = true;
        bool first = true;
        while(!cola.empty()) {
            step actual = cola.top();
            cola.pop();
            //cout << actual.i + 1<< " ";
            for (int j = 0; j < sz; j++) {
                if (vis[j] && ciudad[actual.i][j]) {
                    if ( == j) {
                        cycle = true;
                    }
                }
                if (ciudad[actual.i][j] && !vis[j] && valores[j] <= actual.d + 1) {
                    cola.emplace(j, actual.d + 1);
                    valores[j] = actual.d + 1;
                    vis[j] = true;
                }
            }
            first = false;
        }
        //cout << '\n';
    }
    if (cycle) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < sz; i++) {
        cout << valores[i] << ' ';
    }
    cout << '\n';
    return 0;
}
