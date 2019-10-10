#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

// palabras tomadas de un generador aleatorio
std::string palabras[30] = {
    "forestry", "freshman",   "suitcase",    "chip",       "slam",
    "drag",     "gate",       "integration", "glare",      "degree",
    "stunning", "reject",     "academy",     "remedy",     "shine",
    "hardware", "coma",       "assertive",   "relaxation", "creep",
    "belief",   "revolution", "ambiguity",   "normal",     "cereal",
    "leg",      "pack",       "brother",     "cake",       "lease"};

std::string randomPal() { return palabras[rand() % 30]; }

bool contiene(std::string palabra, std::vector<bool> &revs, char letra) {
    bool corr = false;
    for (int i = 0; i < palabra.size(); i++) {
        if (palabra[i] == letra) {
            revs[i] = true;
            corr = true;
        }
    }
    return corr;
}

bool tirado(std::vector<char> &usadas, char actual) {
    return find(usadas.begin(), usadas.end(), actual) != usadas.end();
}

bool ganador(std::vector<bool> &revs) {
    for (int i = 0; i < revs.size(); i++) {
        if (!revs[i])
            return false;
    }
    return true;
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

void imprimirLetras(std::vector<char> turnos) {
    std::cout << "Letras utilizadas: " << std::endl;
    for (char letra : turnos) {
        std::cout << letra << ", ";
    }
    std::cout << std::endl;
}

void imprimirPalabra(std::string palabra, std::vector<bool> &revs) {
    for (int i = 0; i < palabra.size(); i++) {
        if (revs[i]) {
            std::cout << " " << palabra[i] << " ";
        } else {
            std::cout << " _ ";
        }
    }
    std::cout << std::endl;
}

void imprimirTurno(std::string palabra, std::vector<bool> revs,
                   std::vector<char> turnos, int errores) {
    system("cls");
    imprimirMono(errores);
    imprimirLetras(turnos);
    imprimirPalabra(palabra, revs);
}

bool turno(std::string palabra, std::vector<char> &usadas,
           std::vector<bool> &revs, int errores) {
    imprimirTurno(palabra, revs, usadas, errores);
    char letra;
    std::cout << "Ingrese una letra" << std::endl;
    std::cin >> letra;
    letra = tolower(letra);
    while (tirado(usadas, letra)) {
        std::cout << "Ingrese una letra que no haya utilizado" << std::endl;
        std::cin >> letra;
        letra = tolower(letra);
    }
    usadas.push_back(letra);
    if (contiene(palabra, revs, letra)) {
        std::cout << "La letra ingresada aparece en la palabra" << std::endl;
        return false;
    } else {
        std::cout << "La letra ingresada no aparece en la palabra" << std::endl;
        return true;
    }
}

void juego() {
    int errores = 0;
    std::string palabra = randomPal();
    std::vector<char> turnos;
    std::vector<bool> revs(palabra.size(), false);
    while (errores <= 6) {
        errores += turno(palabra, turnos, revs, errores);

        if (ganador(revs)) {
            std::cout << "Ganaste! la palabra es: " << palabra << std::endl;
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Perdiste" << std::endl;
}

int main() {
    srand(time(NULL));
    std::cout << "Bienvenido al juego del ahorcado" << std::endl;
    std::cout << "Cargando..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
    int a;
    while (true) {
        juego();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        system("cls");
        std::cout << "Desea jugar nuevamente?, ingrese 1 en caso de que si"
                  << std::endl;
        std::cin >> a;
        if (a != 1)
            break;
        system("cls");
        std::cout << "cargando..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
    }

    return 0;
}
