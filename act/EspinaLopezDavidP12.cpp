#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

// Angles measured in gradians
template <typename T>
struct Vector2D {
    bool pol;
    T x, y;
    T magn, deg;
    Vector2D() {}
    Vector2D(T&& px, T&& py, bool p = false) {
        pol = p;
        if (p)
            magn = px, deg = py;
        else
            x = px, y = py;
    }

    Vector2D<T> suma(Vector2D<T> sec) {
        if (pol) {
            Vector2D<T> second = sec.polar();
            T my = sin(deg) * magn + sin(second.deg) * second.magn;
            T mx = cos(deg) * magn + cos(second.deg) * second.magn;
            T res = sqrt(pow(mx, 2) + pow(my, 2));
            T deg = atan(my / mx);
            return Vector2D(res, deg, true);
        }
        return Vector2D<T>(x + sec.x, y + sec.y);
    }

    Vector2D<T> convertir() {
        if (pol)
            return cartesian();
        return polar();
    }

    Vector2D<T> polar() {
        T res = sqrt(pow(x, 2) + pow(y, 2));
        T deg = atan(y / x);
        return Vector2D<T>(res, deg, true);
    }

    Vector2D<T> cartesian() {
        T px = cos(deg) * magn;
        T py = sin(deg) * magn;
        return Vector2D<T>(px, py);
    }

    Vector2D<T> operator+(Vector2D<T> v2) {
        return suma(v2);
    }

    ostream &operator <<(ostream &out) {
        if (polar) 
            return out << "m: " << magn << " a: " << deg << '\n';
        else 
            return out << "x: " << x << " y: " << y << '\n';
    }
};

struct Temporizador {
    int s;
    Temporizador(int min, int seg) { s = min * 60 + seg; }
    Temporizador(int seg) { s = seg; }
    void comenzar() {
        int last = 0;
        std::chrono::time_point<std::chrono::system_clock> inicio =
            std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> fin =
            inicio + std::chrono::seconds(s);
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // To show start at 10
        while (std::chrono::system_clock::now() < fin) {
            int actual = std::chrono::duration_cast<std::chrono::seconds>(
                             fin - std::chrono::system_clock::now())
                             .count() +
                         1; // Offset for counting from 10 to 0, 1 second added
            if (last != actual) {
                system("cls");
                std::cout << ((actual / 60 < 10) ? "0" : "") << actual / 60
                          << ":" << ((actual % 60 < 10) ? "0" : "")
                          << actual % 60 << '\n';
            }
            last = actual;
            std::this_thread::sleep_for(std::chrono::seconds(
                1));  // Avoid wasting resources
        } // The counter ends at 00:01
        std::cout << "00:00\n"; 
    }
};

// A ton of couts for testing the structures
int main() {
    int pos, t;
    float t1, t2;
    while (true) {
        std::cout << "Elija una opcion" << '\n';
        std::cout << "1) Vectores 2D" << '\n';
        std::cout << "2) Temporizador" << '\n';
        std::cout << "3) Salir" << '\n';
        std::cin >> pos;
        while (pos < 1 || pos > 3) {
            std::cout << "Ingrese una opcion valida" << '\n';
            std::cin >> pos;
        }
        if (pos == 1) {
            std::cout << "Elija una opcion para el Vector2D" << '\n';
            std::cout << "1) Suma" << '\n';
            std::cout << "2) Convertir" << '\n';
            std::cin >> pos;
            if (pos < 1 || pos > 2) {
                std::cout << "Ingrese una opcion valida" << '\n';
                std::cin >> pos;
            }
            if (pos == 1) {
                Vector2D<float>* v1;
                Vector2D<float>* v2;
                std::cout << "Elija una opcion para el primer vector" << '\n';
                std::cout << "1) Escalar" << '\n';
                std::cout << "2) Polar" << '\n';
                std::cin >> pos;
                while (pos < 1 || pos > 3) {
                    std::cout << "Ingrese una opcion valida" << '\n';
                    std::cin >> pos;
                }
                if (pos == 1) {
                    std::cout << "Ingrese la coordenada x del vector" << '\n';
                    std::cin >> t1;
                    std::cout << "Ingrese la coordenada y del vector" << '\n';
                    std::cin >> t2;
                    v1 = new Vector2D<float>(t1, t2);
                }
                if (pos == 2) {
                    std::cout << "Ingrese la magnitud del vector" << '\n';
                    std::cin >> t1;
                    std::cout << "Ingrese el angulo del vector (en radianes)" << '\n';
                    std::cin >> t2;
                    v1 = new Vector2D<float>(t1, t2, true);
                }
                std::cout << "Elija una opcion para el segundo vector" << '\n';
                std::cout << "1) Escalar" << '\n';
                std::cout << "2) Polar" << '\n';
                std::cin >> pos;
                while (pos < 1 || pos > 3) {
                    std::cout << "Ingrese una opcion valida" << '\n';
                    std::cin >> pos;
                }
                if (pos == 1) {
                    std::cout << "Ingrese la coordenada x del vector" << '\n';
                    std::cin >> t1;
                    std::cout << "Ingrese la coordenada y del vector" << '\n';
                    std::cin >> t2;
                    v2 = new Vector2D<float>(t1, t2);
                }
                if (pos == 2) {
                    std::cout << "Ingrese la magnitud del vector" << '\n';
                    std::cin >> t1;
                    std::cout << "Ingrese el angulo del vector (en radianes)" << '\n';
                    std::cin >> t2;
                    v2 = new Vector2D<float>(t1, t2, true);
                }
                Vector2D suma = v1->suma(*v2);
                if (suma.pol) {
                    std::cout << "El vector resultante es:" << '\n';
                    std::cout << "magnitud: " << suma.magn << '\n'; 
                    std::cout << "angulo: " << suma.deg << '\n'; 
                } else {
                    std::cout << "El vector resultante es:" << '\n';
                    std::cout << "x: " << suma.x << '\n'; 
                    std::cout << "y: " << suma.y << '\n'; 
                }
                delete v1;
                delete v2;
            }
            if (pos == 2) {
                std::cout << "Elija el tipo de vector a convertir" << '\n';
                std::cout << "1) Polar" << '\n';
                std::cout << "2) Escalar" << '\n';
                std::cin >> pos;
                while (pos < 1 || pos > 2) {
                    std::cout << "Ingrese una opcion valida" << '\n';
                    std::cin >> pos;
                }
                if (pos == 1) {
                    std::cout << "Ingrese la coordenada x del vector" << '\n';
                    std::cin >> t1;
                    std::cout << "Ingrese la coordenada y del vector" << '\n';
                    std::cin >> t2;
                    Vector2D<float> v1(t1, t2);
                    Vector2D<float> transformado = v1.convertir();
                    std::cout << "El vector transformado es:" << '\n';
                    std::cout << "magnitud:" << transformado.magn << '\n';
                    std::cout << "angulo:" << transformado.deg << '\n';
                }
                if (pos == 2) {
                    std::cout << "Ingrese la magnitud del vector" << '\n';
                    std::cin >> t1;
                    std::cout << "Ingrese el angulo del vector" << '\n';
                    std::cin >> t2;
                    Vector2D<float> v1(t1, t2, true);
                    Vector2D<float> transformado = v1.convertir();
                    std::cout << "El vector transformado es:" << '\n';
                    std::cout << "x:" << transformado.x << '\n';
                    std::cout << "y:" << transformado.y << '\n';
                }
            }
            continue;
        }
        if (pos == 2) {
            std::cout << "Elija una opcion para iniciar el temporizador" << '\n';
            std::cout << "1) Segundos" << '\n';
            std::cout << "2) Minutos y segundos" << '\n';
            std::cin >> pos;
            while (pos < 1 || pos > 2) {
                std::cout << "Ingrese una opcion valida" << '\n';
                std::cin >> pos;
            }
            if (pos == 1) {
                std::cout << "Ingrese la cantidad de segundos del temporizador:" << '\n';
                std::cin >> t;
                Temporizador a(t);
                std::cout << "Iniciando temporizador" << '\n';
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                a.comenzar();
            }
            if (pos == 2) {
                std::cout << "Ingrese la cantidad de minutos del temporizador:" << '\n';
                std::cin >> pos;
                std::cout << "Ingrese la cantidad de segundos del temporizador:" << '\n';
                std::cin >> t;
                Temporizador a(pos, t);
                std::cout << "Iniciando temporizador" << '\n';
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                a.comenzar();
            }
            continue;
        }
        if (pos == 3)
            break;
    }
}
