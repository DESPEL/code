#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

struct ficha {
    ficha(int c) { color = c; }
    int color;
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
};

class dado {};
