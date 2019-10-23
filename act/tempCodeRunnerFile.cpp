#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

struct Fract {
    Fract() {}
    Fract(long long int n, long long int d) {
        num = n;
        den = d;
    }
    long long int num;
    long long int den;
};

std::ostream &operator<<(std::ostream &out, const Fract &fr) {
    return out << fr.num << "/" << fr.den;
}

std::istream &operator>>(std::istream &in, Fract &frac) {
    string num, temp;
    int i;
    while (true) {
        in >> num;
        bool div = false;
        bool correcto = true;
        for (char c : num) {
            if (c < '0' || c > '9') {
                if (c != '/') {
                    correcto = false;
                    break;
                }
                if (div) {
                    correcto = false;
                    break;
                }
                div = true;
            }
        }
        if (correcto && div) {
            break;
        }
        cout << "Ingrese una fraccion en la forma a/b" << endl;
    }

    for (i = 0; i < num.size(); i++) {
        if (num[i] == '/')
            break;
        temp += num[i];
    }
    int numerador = stoi(temp);
    temp = "";
    i++;
    for (; i < num.size(); i++) {
        temp += num[i];
    }
    int denominador = stoi(temp);
    frac.num = numerador;
    frac.den = denominador;
    return in;
}

// Operador para multiplicar fracciones
Fract operator*(Fract n1, Fract n2) {
    long long int num = n1.num * n2.num;
    long long int den = n1.den * n2.den;
    return Fract(num, den);
}

Fract operator/(Fract n1, Fract n2) {
    long long int num = n1.num * n2.den;
    long long int den = n1.den * n2.num;
    return Fract(num, den);
}

void multiplicarF() {
    Fract f1;
    Fract f2;
    cout << "Ingrese las fracciones en la forma a/b ejemplo: 5/100" << endl;
    cout << "Ingrese la primera fraccion" << endl;
    cin >> f1;
    cout << "Ingrese la segunda fraccion" << endl;
    cin >> f2;
    cout << "El resultado de la multiplicacion es:" << endl;
    cout << f1 * f2 << endl;
}

void sumaDec() {
    cout << "Ingrese la cantidad de numeros a sumar" << endl;
    int n;
    cin >> n;
    float val, res = 0;
    for (int i = 0; i < n; i++) {
        cout << "Ingrese el numero en la posicion " << i + 1 << endl;
        cin >> val;
        res += val;
    }
    cout << "El resultado de la suma es:" << endl;
    cout << res << endl;
}

int main() {
    sumaDec();
    multiplicarF();
}
