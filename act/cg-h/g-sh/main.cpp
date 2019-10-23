#include <iostream>
#include <thread>
#include <chrono>

#include "gato.hpp"
#include "cajas.hpp"
#include "ahorcado.hpp"

using namespace std;

typedef void (*jgs) ();

jgs juegos[] = {gato::run, cajas::run, ahorcado::run};

void imprimirMenu() {
    cout << "1) gato" << endl;
    cout << "2) cajas" << endl;
    cout << "3) ahorcado" << endl;
}

int main () {
    srand(time(NULL));
    while (true) {
        imprimirMenu();
        int n;
        cin >> n;
        while (n < 1 || n > 3) {
            cout << "Ingrese un juego valido" << endl;
            cin >> n;
        }
        juegos[n -1]();
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
        cout << "Si desea jugar nuevamente ingrese 1" << endl;
        cin >> n;
        if (n != 1) break;
        system("cls");
    }
}