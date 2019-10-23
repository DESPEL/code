#include <iostream>
#include "2puntos.hpp"
#include "blackjack.hpp"

using namespace std;

int main() {
    while (true) {
        cout << "Ingrese una opcion" << endl;
        cout << "1) Coordenadas de puntos" << endl;
        cout << "2) Blackjack" << endl;
        cout << "3) Salir" << endl;
        int n;
        cin >> n;
        while (n < 1 || n > 3) {
            cout << "Ingrese una opcion valida" << endl;
            cin >> n;
        }
        system("cls");
        if (n == 3)
            break;
        if (n == 1) {
            cout << "Ingrese una opcion" << endl;
            cout << "1) Funcion lineal entre 2 puntos" << endl;
            cout << "2) Distancia entre 2 puntos 2d" << endl;
            cout << "3) distancia entre 2 puntos 3d" << endl;
            int n2;
            cin >> n2;
            while (n2 < 1 || n2 > 3) {
                cout << "Ingrese una opcion valida" << endl;
                cin >> n2;
            }
            system("cls");
            if (n2 == 1) {
                punto2d p1, p2;
                cin >> p1 >> p2;
                cout << puntos::ecuacion(p1, p2) << endl;
            }
            if (n2 == 2) {
                punto2d p1, p2;
                cin >> p1 >> p2;
                cout << puntos::distance(p1, p2) << endl;
            }
            if (n2 == 3) {
                punto3d p1, p2;
                cin >> p1 >> p2;
                cout << puntos::distance(p1, p2) << endl;
            }
        } else {
            blackjack::run();
        }
    }
}