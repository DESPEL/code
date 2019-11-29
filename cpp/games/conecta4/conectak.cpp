#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

struct ficha {
    ficha(char c) {
        color = c;
    }  // Habíamos dicho de usar un char para representarlo de la manera que
       // gusten
    char color;
};

struct jugador {
    int turno;
    ficha pieza;
};

template <size_t n = 2>
class jugadores {
private:
    vector<jugador> jugs(n);

public:
    jugadores() {}
    void turnos() {}
}

class tablero {
    // Tablero de m*n, constructor?
};

class dado {
    // generación de un dado para distribuir turnos
};

int main() {}