#include <bits/stdc++.h>

using namespace std;

void mostrar1aN(int n) {
    for (int i = 1; i <= n; i++) {
        cout << i << " ";
    }
    cout << endl;
}

int sumaParesMenoresAN(int n) {
    int suma = 0;
    for (int i = 0; i < n; i += 2) {
        suma += i;
    }
    return suma;
}

inline int nAlCuadrado(int n) {
    return n * n;
}

int main () {
    int n;
    cout << "Ingrese un numero para calcular imprimir "
    "los numeros del 1 al numero, sumar todos los "
    "multiplos de 2 menores al numero y mostrar el valor del numero al cuadrado" << endl;
    cin >> n;
    mostrar1aN(n);
    cout << sumaParesMenoresAN(n) << endl;
    cout << nAlCuadrado(n) << endl;

}
