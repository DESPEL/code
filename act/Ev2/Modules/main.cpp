#include <iostream>
#include <thread>
#include <chrono>

import games.ahorcado;
import games.blackjack;
import games.cajas;
import games.gato;

using namespace std;

typedef void (*jgs) ();

jgs juegos[] = {gato::run, cajas::run, ahorcado::run, blackjack::run};

void imprimirMenu() {
    cout << "Bienvenido al arcade, ingrese el numero de un juego" << endl;
    cout << "1) gato" << endl;
    cout << "2) cajas" << endl;
    cout << "3) ahorcado" << endl;
    cout << "4) blackjack" << endl;
    cout << "5) salir" << endl;
}

int main () {
    srand(time(NULL));
    while (true) {
        imprimirMenu();
        int n;
        cin >> n;
        while (n < 1 || n > 5) {
            cout << "Ingrese un juego valido" << endl;
            cin >> n;
        }
        if (n == 5) break;
        juegos[n -1]();
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
    }
}