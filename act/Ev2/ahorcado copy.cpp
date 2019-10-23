#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

#include "ahorcado.hpp"

namespace ahorcado {

struct pal {
    pal(char l) { letra = l, rev = false; }
    char letra;
    bool rev;
};

struct game {
    game(std::string pala) {
        palabra = pala;
        for_each(begin(pala), end(pala), [&](char &c) {p.push_back(pal(c));});
        //for (char &c : pala) p.push_back(pal(c));
    }
    std::string palabra;
    std::vector<pal> p;
    std::vector<char> turnos;
    int errores = 0;
};

// palabras tomadas de un generador aleatorio
std::string palabras[30] = {
    "forestry", "freshman",   "suitcase",    "chip",       "slam",
    "drag",     "gate",       "integration", "glare",      "degree",
    "stunning", "reject",     "academy",     "remedy",     "shine",
    "hardware", "coma",       "assertive",   "relaxation", "creep",
    "belief",   "revolution", "ambiguity",   "normal",     "cereal",
    "leg",      "pack",       "brother",     "cake",       "lease"};

std::string randomPal() { return palabras[rand() % 30]; }

bool contiene(game &ac, char letra) {
    bool has =
        find(begin(ac.palabra), end(ac.palabra), letra) != end(ac.palabra);
    if (!has)
        return false;
    for_each(begin(ac.p), end(ac.p),
             [&, letra](pal &l) { (l.letra == letra) ? l.rev = true : l.rev = l.rev; });
    return true;
}

bool tirado(std::vector<char> &usadas, char actual) {
    return find(usadas.begin(), usadas.end(), actual) != usadas.end();
}

bool ganador(std::vector<pal> &revs) {
    return std::find_if(begin(revs), end(revs), [](pal &l) { return !l.rev;}) == end(revs);
}

void imprimirMono(int n) {
    if (n >= 1) {
        std::cout << "    -----    " << std::endl;
        std::cout << "    |   |    " << std::endl;
        std::cout << "    -----    " << std::endl;
    }
    if (n >= 2) {
        std::cout << "      |      " << std::endl;
    }
    if (n >= 3) {
        std::cout << "    --|";
        if (n == 3)
            std::cout << std::endl;
    }
    if (n >= 4) {
        std::cout << "--" << std::endl;
    }
    if (n >= 3) {
        std::cout << "      |      " << std::endl;
    }
    if (n >= 5) {
        std::cout << "     " << ((n >= 6) ? "/\\" : "/") << std::endl;
        std::cout << "    " << ((n >= 6) ? "/  \\" : "/") << std::endl;
    }
}

void imprimirLetras(std::vector<char> &turnos) {
    std::cout << "Letras utilizadas: " << std::endl;
    for_each(begin(turnos), end(turnos),
             [](char &val) { std::cout << std::string(1, val) << ", "; });
    std::cout << std::endl;
}

void imprimirPalabra(std::vector<pal> &p) {
    for_each(begin(p), end(p), [&](pal &l) {
        std::cout << (l.rev ? std::string(1, l.letra) : "_") << " ";
    });
    std::cout << std::endl;
}

void imprimirTurno(game &actual) {
    system("cls");
    imprimirMono(actual.errores);
    imprimirLetras(actual.turnos);
    imprimirPalabra(actual.p);
}

bool turno(game &actual) {
    imprimirTurno(actual);
    char letra;
    std::cout << "Ingrese una letra" << std::endl;
    std::cin >> letra;
    letra = tolower(letra);
    while (tirado(actual.turnos, letra)) {
        std::cout << "Ingrese una letra que no haya utilizado" << std::endl;
        std::cin >> letra;
        letra = tolower(letra);
    }
    actual.turnos.push_back(letra);
    if (contiene(actual, letra)) {
        std::cout << "La letra ingresada aparece en la palabra" << std::endl;
        return false;
    } else {
        std::cout << "La letra ingresada no aparece en la palabra" << std::endl;
        return true;
    }
}

void juego() {
    game actual(randomPal());
    while (actual.errores <= 6) {
        actual.errores += turno(actual);
        if (ganador(actual.p)) {
            std::cout << "Ganaste! la palabra es: " << actual.palabra << std::endl;
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Perdiste" << std::endl;
}

void run() {
    std::cout << "Bienvenido al juego del ahorcado" << std::endl;
    std::cout << "Cargando..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
    int a;
    juego();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    system("cls");
}

}  // namespace ahorcado