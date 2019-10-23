#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <thread>

export module games.ahorcado;

template <typename T>

// Implementación de vector
struct vector {
    size_t max_size;
    size_t asz = 0;
    T *container;
    vector(int m_sz = 0, T defval = 0) {
        max_size = m_sz;
        container = new T[m_sz];
        // Simular inicializacion de variables por defecto
        for (int i = 0; i < m_sz; i++) {
            container[i] = defval;
        }
        asz = m_sz;
    }
    // Simular funciones de std::vector para no reescribir el código
    int size() { return asz; }

    void pop_back() { asz--; }

    void push_back(T element) {
        if (asz >= max_size) {
            resize(max_size + 15);
        }
        container[asz] = element;
        asz++;
    }
    // Implementación lineal, iteradores no implementados
    void resize(int n) {
        T *temp = container;
        container = new T[n];
        for (size_t i = 0; i < asz; i++) container[i] = temp[i];
        // liberar memoria
        delete[] temp;
        max_size = n;
    }
    // Compatibilidad con acceso por corchetes
    T &operator[](size_t idx) { return container[idx]; }
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

bool contiene(std::string palabra, vector<bool> &revs, char letra) {
    bool corr = false;
    for (int i = 0; i < palabra.size(); i++) {
        if (palabra[i] == letra) {
            revs[i] = true;
            corr = true;
        }
    }
    return corr;
}

bool tirado(vector<char> &usadas, char actual) {
    for (int i = 0; i < usadas.size(); i++) {
        if (usadas[i] == actual) {
            return true;
        }
    }
    return false;
}

bool ganador(vector<bool> &revs) {
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

void imprimirLetras(vector<char> turnos) {
    std::cout << "Letras utilizadas: " << std::endl;
    for (int i = 0; i < turnos.size(); i++) {
        std::cout << turnos[i] << ", ";
    }
    std::cout << std::endl;
}

void imprimirPalabra(std::string palabra, vector<bool> &revs) {
    for (int i = 0; i < palabra.size(); i++) {
        if (revs[i]) {
            std::cout << " " << palabra[i] << " ";
        } else {
            std::cout << " _ ";
        }
    }
    std::cout << std::endl;
}

void imprimirTurno(std::string palabra, vector<bool> revs, vector<char> turnos,
                   int errores) {
    system("cls");
    imprimirMono(errores);
    imprimirLetras(turnos);
    imprimirPalabra(palabra, revs);
}

bool turno(std::string palabra, vector<char> &usadas, vector<bool> &revs,
           int errores) {
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
    vector<char> turnos;
    vector<bool> revs(palabra.size(), false);
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

export namespace ahorcado {
    void run() {
        std::cout << "Bienvenido al juego del ahorcado" << std::endl;
        std::cout << "Cargando..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
        juego();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        system("cls");
    }
}