#include <algorithm>
#include <cmath>
#include <iostream>

struct Fract {
    Fract() {}
    Fract(long long int n, long long int d) {
        num = n;
        den = d;
    }
    long long int num;
    long long int den;

    Fract operator*(Fract n1) { return Fract(num * n1.num, den * n1.den); }
};

std::ostream &operator<<(std::ostream &out, const Fract &fr) {
    return out << fr.den << "/" << fr.num;
}

class Num {
    long long int numerador;
    long long int denominador;
    float decimal;
    bool frac;

public:
    Num(float dec) {
        frac = false;
        decimal = dec;
    }
    Num(long long int num, long long int den) {
        numerador = num;
        denominador = den;
        frac = true;
    }

    Fract fr() {
        if (frac) {
            return Fract(numerador, denominador);
        }
        int den = 10;
        float temp = decimal;
        while (fmod(temp, 1) != 0) {
            temp *= den;
            den *= 10;
        }

        return Fract(temp, den);
    }

    float dec() {
        if (frac) {
            return (float)numerador / (float)denominador;
        }
        return decimal;
    }

    bool isFloat() { return !frac; }

    Num operator*(Num n1) {
        if (n1.isFloat() && !frac) {
            return Num(n1.dec() * decimal);
        }
        Fract t1 = n1.fr();
        Fract t2 = fr();
        Fract res = t2 * t1;
        return Num(res.num, res.den);
    }
};

int main() {
    Num prueba(10.9f);
    std::cout << prueba.dec() << std::endl;
    Fract test = prueba.fr();
    std::cout << std::endl;
}
