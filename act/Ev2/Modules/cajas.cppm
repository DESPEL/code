#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <thread>

#define NCAJAS 8
#define MINV 1
#define MAXV 50

export module games.cajas;

using namespace std;

int random(int min, int max) { return min + (rand() % (max - min + 1)); }

void rellenar(int cajas[]) {
    for (int i = 0; i < NCAJAS; i++) {
        cajas[i] = random(MINV, MAXV);
    }
    cout << endl;
}

void mostrarCajas(int cajas[], bool abiertas[]) {
    cout << "|";
    for (int i = 0; i < NCAJAS; i++) {
        if (abiertas[i]) {
            cout << cajas[i];
        } else {
            cout << (char)('A' + i);
        }
        cout << "|";
    }
    cout << endl;
}

void mostrarPuntos(int p1, int p2) {
    cout << "El jugador 1 lleva " << p1 << " puntos" << endl;
    cout << "El jugador 2 lleva " << p2 << " puntos" << endl;
}

void imprimirGanador(int jugador, int puntos) {
    cout << "El jugador " << jugador << " ha ganado  con " << puntos
         << " puntos" << endl;
}

int turno(int cajas[], bool abiertas[], int jugador) {
    char caja;
    cout << "Jugador " << jugador << " elija una caja" << endl;
    cin >> caja;
    while (abiertas[toupper(caja) - 'A'] ||
           (toupper(caja) > 'H' || toupper(caja) < 'A')) {
        if (toupper(caja) > 'H' || toupper(caja) < 'A')
            cout << "Elija una caja dentro del rango" << endl;
        else
            cout << "Elija una caja que no haya sido abierta" << endl;
        cin >> caja;
    }
    abiertas[toupper(caja) - 'A'] = true;
    return cajas[toupper(caja) - 'A'];
}

int turnoComp(int cajas[], bool abiertas[]) {
    int caja = random(0, NCAJAS - 1);
    while (abiertas[caja]) {
        caja = random(0, NCAJAS - 1);
    }
    abiertas[caja] = true;
    cout << "La computadora eligio la caja: " << (char)('A' + caja) << endl;
    return cajas[caja];
}

int juegoSolo(int cajas[], bool abiertas[], int puntos[]) {
    for (int i = 0; i < 6; i++) {
        mostrarCajas(cajas, abiertas);
        mostrarPuntos(puntos[0], puntos[1]);
        if (i % 2 == 0) {
            puntos[i % 2] += turno(cajas, abiertas, (i % 2) + 1);
        } else {
            puntos[i % 2] += turnoComp(cajas, abiertas);
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
        system("cls");
    }
    return (puntos[2] > puntos[1]) ? 2 : 1;
}

int juegoMulti(int cajas[], bool abiertas[], int puntos[]) {
    for (int i = 0; i < 6; i++) {
        mostrarCajas(cajas, abiertas);
        mostrarPuntos(puntos[0], puntos[1]);
        puntos[i % 2] += turno(cajas, abiertas, (i % 2) + 1);
        this_thread::sleep_for(chrono::milliseconds(750));
        system("cls");
    }
    return (puntos[2] > puntos[1]) ? 2 : 1;
}

void juego(int solo = 0) {
    int cajas[NCAJAS];
    rellenar(cajas);
    bool abiertas[NCAJAS] = {false};
    int puntos[2]{0};
    int ganador = 0;
    if (solo == 0) {
        ganador = juegoSolo(cajas, abiertas, puntos);
    } else {
        ganador = juegoMulti(cajas, abiertas, puntos);
    }
    imprimirGanador(ganador, puntos[ganador - 1]);
}

export namespace cajas {
    void run() {
        int solo;
        cout << "Si desea jugar contra la computadora ingrese 0" << endl;
        cin >> solo;
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
        juego(solo);
    }
}