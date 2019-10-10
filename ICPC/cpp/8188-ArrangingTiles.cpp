#include <iostream>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

int **alturas;
int **regiones;
int r, c;

struct coord {
    int regid;
    int r;
    int c;
};

int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

void marcar() {
    int regN = 0;
    bool revs[r][c];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            revs[i][j] = false;
        }
    }

    struct coord currCoord;
    queue<coord> capa;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (revs[i][j]) continue;
            revs[i][j] = true;
            currCoord.r = i;
            currCoord.c = j;
            capa.push(currCoord);
            while (!capa.empty()) {
                coord curr = capa.front();
                capa.pop();
                revs[curr.r][curr.c] = true;
                regiones[curr.r][curr.c] = regN;
                for (int k = 0; k < 4; k++) {
                    if (curr.r + dr[k] >= 0 && curr.c + dc[k] >= 0 && curr.r + dr[k] < r && curr.c + dc[k] < c ) {
                        if (!revs[curr.r + dr[k]][curr.c + dc[k]]) {
                            if (alturas[curr.r + dr[k]][curr.c + dc[k]] == alturas[curr.r][curr.c]) {
                                currCoord.r = curr.r + dr[k];
                                currCoord.c = curr.c + dc[k];
                                capa.push(currCoord);
                            }
                        }
                    }
                }
            }
            regN++;
            for (int j = 0; j < r; j++) {
                for (int k = 0; k < c; k++) {
                    cout << revs[j][k] << " ";
                }
                cout << endl;
            }
        }
    }
}

int main () {
    cin >> r >> c;

    alturas = new int*[r];
    regiones = new int*[r];
    for (int i = 0; i < c; i++) {
        alturas[i] = new int[c];
        regiones[i] = new int[c];
    }

    for(int i = 0; i < r; i++) {
        for (int j = 0; j < c;j++) {
            regiones[i][j] = -1;
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> alturas[i][j];
        }
    }

    marcar();

    cout << endl;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << regiones[i][j] << " ";
        }
        cout << "\n";
    }

    int caras = 5;

}
