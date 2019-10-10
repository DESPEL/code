#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <thread>

using namespace std;

int random() { return (rand() % 3); }

void imprimirTablero(int tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char pchar = '.';
            if (tablero[i][j] == 1)
                pchar = 'o';
            if (tablero[i][j] == 2)
                pchar = 'x';
            cout << " " << pchar << ((j < 2) ? " |" : "\n");
        }
        cout << ((i < 2) ? "___|___|___" : "   |   |   ") << endl;
    }
}

void imprimirGanador(int ganador = 0) {
    switch (ganador) {
    case 1:
        cout << "El jugador 1 ha ganado" << endl;
        break;
    case 2:
        cout << "El jugador 2 ha ganado" << endl;
        break;
    default:
        cout << "Nadie ha ganado" << endl;
    }
}

void turno(int tablero[3][3], int jugador) {
    int r, c;
    cout << "Jugador " << jugador << " ingrese la fila y la columna de su tiro"
         << endl;
    cin >> r >> c;
    while (r > 3 || r < 1 || c < 1 || c > 3 || tablero[r - 1][c - 1] != 0) {
        if (tablero[r - 1][c - 1] != 0)
            cout << "Ingrese una casilla vacia" << endl;
        else
            cout << "La fila y columna deben de estar entre 1 y 3 inclusive"
                 << endl;
        cin >> r >> c;
    }
    tablero[r - 1][c - 1] = jugador;
}

void turnoComp(int tablero[3][3]) {
    int r = random(), c = random();
    while (tablero[r][c] != 0) {
        r = random(), c = random();
    }
    tablero[r][c] = 2;
    cout << "La computadora eligio la casilla " << r + 1 << ", " << c + 1
         << endl;
    ;
}

bool lleno(int tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == 0)
                return false;
        }
    }
    return true;
}

bool verificarGanador(int tablero[3][3]) {
    int fp = 0;
    int contig = 1;
    for (int i = 0; i < 3; i++) {
        fp = tablero[i][0];
        contig = 1;
        for (int j = 1; j < 3; j++) {
            if (tablero[i][j] == fp && fp != 0) {
                contig++;
            }
        }
        if (contig >= 3)
            return true;
        contig = 0;
    }
    for (int i = 0; i < 3; i++) {
        fp = tablero[0][i];
        contig = 1;
        for (int j = 1; j < 3; j++) {
            if (tablero[j][i] == fp && fp != 0) {
                contig++;
            }
        }
        if (contig >= 3)
            return true;
        contig = 0;
    }
    fp = tablero[0][0];
    if (fp != 0 && (tablero[1][1] == fp && tablero[2][2] == fp))
        return true;
    fp = tablero[2][0];
    if (fp != 0 && (tablero[1][1] == fp && tablero[0][2] == fp))
        return true;

    return false;
}

int juego(int solo) {
    int tablero[3][3] = {0};
    int jugador = 1;
    while (!lleno(tablero)) {
        imprimirTablero(tablero);
        if (solo == 0) {
            if (jugador == 1)
                turno(tablero, jugador);
            else
                turnoComp(tablero);
        } else {
            turno(tablero, jugador);
        }

        this_thread::sleep_for(chrono::milliseconds(750));
        system("cls");

        if (verificarGanador(tablero))
            return jugador;
        jugador = (jugador % 2) + 1;
    }
    return 0;
}

int main() {
    srand(time(NULL));
    while (true) {
        int n;
        cout << "Si desea jugar contra la computadora ingrese 0" << endl;
        cin >> n;
        imprimirGanador(juego((n == 0) ? 0 : 1));
        cout << "Si desea seguir jugando ingrese 1" << endl;
        cin >> n;
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
    }
}