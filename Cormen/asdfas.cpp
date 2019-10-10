#include <ctime>
#include <iostream>
#include <random>

#define TAM 8

using namespace std;

int valMin = 1;
int valMax = 50;

// tablero   = {20, 30, 40}
// revisados = {false, true, false}
void mostrarT(int tablero[TAM], bool revisados[TAM]) {
    int i = 0;
    cout << "|";
    while (i < TAM) {
        if (revisados[i]) {
            // imprimimos el numero
            cout << tablero[i] << "|";
        } else {
            // imprimimos la letra
            cout << (char)('A' + i) << "|";
        }
        i++;
    }
    cout << endl;
}

int random(int min, int max) { return min + (rand() % (max - min + 1)); }

void llenarCajas(int tablero[TAM]) {
    for (int i = 0; i < TAM; i++) {
        tablero[i] = random(valMin, valMax);
    }
}

int turnoP(int jugador, bool revisados[TAM], int tablero[TAM]) {
    char caja;
    cout << "jugador " << jugador << " elija una caja" << endl;
    cin >> caja;
    caja = toupper(caja);
    while (caja < 'A' || caja > 'H' || revisados[caja - 'A']) {
        cout << "Elije una caja dentro del rango y que no este revisada"
             << endl;
        cin >> caja;
        caja = toupper(caja);
    }
    revisados[caja - 'A'] = true;
    return tablero[caja - 'A'];
}

int turnoC(bool revisados[TAM], int tablero[TAM]) {
    cout << "La computadora eligio la caja: ";
    int tiro = random(0, TAM - 1);
    while (revisados[tiro]) {
        tiro = random(0, TAM - 1);
    }
    revisados[tiro] = true;
    return tablero[tiro];
}

void imprimirGanador(int p1, int p2) {
    if (p1 > p2) {
        cout << "Gano el jugador 1" << endl;
    }
    if (p2 > p1) {
        cout << "Gano el jugador 2" << endl;
    }
    if (p1 == p2) {
        cout << "Empate " << endl;
    }
}

void juego1() {
    int tablero[TAM];
    bool revisados[TAM];
    for (int i = 0; i < TAM; i++) {
        revisados[i] = false;
    }
    llenarCajas(tablero);

    int jugador = 1;
    int pj = 0, pc = 0;
    for (int i = 0; i < 6; i++) {
        mostrarT(tablero, revisados);

        if (jugador == 1) {
            pj += turnoP(jugador, revisados, tablero);
            cout << "El jugador 1 lleva " << pj << " puntos" << endl;
        }
        if (jugador == 2) {
            pc += turnoC(revisados, tablero);
            cout << "El jugador 2 lleva " << pc << " puntos " << endl;
        }

        if (jugador == 1) {
            jugador = 2;
        } else {
            jugador = 1;
        }
    }

    imprimirGanador(pj, pc);
}

void juego2() {
    int tablero[TAM];
    bool revisados[TAM];
    for (int i = 0; i < TAM; i++) {
        revisados[i] = false;
    }
    llenarCajas(tablero);

    int jugador = 1;
    int pj = 0, pc = 0;
    for (int i = 0; i < 6; i++) {
        mostrarT(tablero, revisados);

        if (jugador == 1) {
            pj += turnoP(jugador, revisados, tablero);
            cout << "El jugador 1 lleva " << pj << " puntos" << endl;
        }
        if (jugador == 2) {
            pc += turnoP(jugador, revisados, tablero);
            cout << "El jugador 2 lleva " << pc << " puntos " << endl;
        }

        if (jugador == 1) {
            jugador = 2;
        } else {
            jugador = 1;
        }
    }

    imprimirGanador(pj, pc);
}

int mostrarM() {
    int njugadores;
    cout << "ingrese n jugadores" << endl;
    cin >> njugadores;
    while (njugadores < 1 || njugadores > 2) {
        cout << "ingresa un valor entre 1 y 2" << endl;
        cin >> njugadores;
    }
    return njugadores;
}

void juego() {
    int njugadores = mostrarM();

    if (njugadores == 1) {
        juego1();
    } else {
        juego2();
    }
}

int main() {
    srand(time(NULL) % 100);
    int seguir = 1;
    while (seguir) {
        juego();
        cout << "si quiere dejar de jugar ingrese 0" << endl;
        cin >> seguir;
    }
}
