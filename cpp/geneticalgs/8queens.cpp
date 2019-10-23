#include <iostream>
#include <vector>

using namespace std;

struct reina {
    int x;
    int y;
};
bool original[8][8] = {{false}};

bool verificar (bool tablero[8][8], int x, int y) {
    if (x >= 8 || y >= 8) return false;
    for (int i = 0; i < 8; i++) {
        //cout << "1" << endl;
        if (tablero[i][y] && i != x) return false;
    }
    for (int j = 0; j < 8; j++) {
        //cout << "2" << endl;
        if (tablero[x][j] && j != y) return false;
    }
    for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
        //cout << "3" << endl;
        if (tablero[i][j]) return false;
    }
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        //cout << "4" << endl;
        if (tablero[i][j]) return false;
    }
    for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
        //cout << "5" << endl;
        if (tablero[i][j]) return false;
    }
    for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
        //cout << "6" << endl;
        if (tablero[i][j]) return false;
    }
    return true;
}

bool ponerReina(bool tablero[8][8], int x, int y) {
    if (verificar(tablero, x, y)) {
        tablero[x][y] = true;
        return true;
    }
    return false;
}

bool quitarReina(bool tablero[8][8], int x, int y) {
    if (x >= 8 || y >= 8) return false;
    if (original[x][y]) return false;
    tablero [x][y] = false;
    return true;
}

int encontrarReina(bool tablero[8][8], int x, int y) {
    for (int i = 0; i < 8; i++) {
        if (tablero[x][i]) {
            return i;
        }
    }
    return y;
}

vector<int> coordx;
vector<int> coordy;
bool ponerReinas(bool tablero[8][8], int *n = 0, int x = 0, int y = 0) {
    //if (x >= 8 || y >= 8) return true;
    if (!ponerReina(tablero, x, y)) {
        if (x == 0) {
            return ponerReinas(tablero, n, x, y + 1);
        }
        return false;
    }
    coordx.push_back(x);
    coordy.push_back(y);
    for (int i = 0; i < 8; i++) {
        if(!ponerReinas(tablero, n, x + 1, i)) {
            quitarReina(tablero, x + 1, i);
        }
    }
    if (coordx.size() == 8) return true;
    coordx.pop_back();
    coordy.pop_back();
    return false;
}

void imprimir(bool tablero[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

int main () {
    bool tablero[8][8] = {{false}};
    ponerReinas(tablero);
    /*
    for (int i = 0; i < coordx.size(); i++) {
        cout << coordx[i] + 1 << " " << coordy[i] + 1 << endl;;
    }*/ // IMprimir coordenadas
    imprimir(tablero);
}