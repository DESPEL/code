#include <ctime>
#include <iostream>
#include <random>
#include <thread>

#define NDECK 1           // Establecer numero de barajas
#define NCARDS 52         // Numero de cartas - no tocar
#define MAX_SZ_HAND 27    // Numero máximo de cartas en mano - no relevante
#define MAX_SPLIT 4       // Splits máximos
#define SHUFFLE_PERMS 50  // Permutaciones al revovler
#define card int          // Simulacion struct card { int val; }

export module games.blackjack;

using namespace std;

int random(int min = 0, int max = 52) {
    return min + (rand() % (max - min + 1));
}

struct deck {
    card cartas[NCARDS * NDECK];
    int size = NCARDS * NDECK;
    deck() {
        // populate deck
        for (int i = 1; i <= NDECK; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 13; k++) {
                    cartas[i * j * 13 + k] = (k < 10) ? k + 1 : 10;
                }
            }
        }
        // shuffle
        for (int i = 0; i < SHUFFLE_PERMS; i++) {
            int n1 = random(0, 51), n2 = random(0, 51);
            card temp = cartas[n1];
            cartas[n1] = cartas[n2];
            cartas[n2] = temp;
        }
    }

    card take() {
        card carta = cartas[size - 1];
        size--;
        return carta;
    }
};

struct jugador {
    card manos[MAX_SPLIT][MAX_SZ_HAND];
    int nmanos = 1;
    card sizes[MAX_SPLIT] = {0};
    card as[MAX_SPLIT];
    jugador() {
        // Clean memory
        for (int i = 0; i < MAX_SPLIT; i++) {
            for (int j = 0; j < MAX_SZ_HAND; j++) {
                manos[i][j] = 0;
            }
        }
    }

    void push_back(card val, int idx = 0) {
        manos[idx][sizes[idx]] = val;
        sizes[idx]++;
    }

    int maxpoints(int mano = 0) {
        int min = 0;
        for (card carta : manos[mano]) {
            if (carta != 1)
                min += carta;
        }
        return getmax(min, as[mano]);
    }

    int getmax(int lv = 0, int as = 0) {
        if (lv > 21)
            return -1;
        if (as == 0)
            return lv;
        int v1 = getmax(lv + 11, as - 1);
        v1 = (v1 > 21) ? -1 : v1;
        int v2 = getmax(lv + 1, as - 1);
        v2 = (v2 > 21) ? -1 : v2;
        if (v1 && v2 == -1)
            return -1;
        if (v1 > v2)
            return v1;
        else
            return v2;
    }

    void divideHands() {
        nmanos++;
        card unique = manos[0][0];
        for (int i = 0; i < nmanos; i++) {
            manos[i][0] = unique;
            sizes[i] = 1;
            if (unique == 1)
                as[i] = 1;
        }
    }

    void add(int idx, card actual) {
        push_back(actual, idx);
        if (actual == 1)
            as[idx]++;
    }
};

void terminar(deck *juego, jugador *p, jugador *comp) {
    system("cls");
    cout << "Calculando ganador..." << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");

    int dealerpoints = comp->maxpoints(0);
    int *jpoints = new int[p->nmanos];
    for (int i = 0; i < p->nmanos; i++) {
        jpoints[i] = p->maxpoints(i);
    }

    for (int i = 0; i < p->nmanos; i++) {
        if (jpoints[i] == -1 && dealerpoints == -1) {
            cout << "Nadie ganó con la mano " << i + 1 << endl;
        } else if (jpoints[i] == -1 || dealerpoints == -1) {
            if (jpoints[i] == -1) {
                cout << "El dealer ha ganado con " << dealerpoints
                     << "puntos para la mano " << i + 1 << endl;
                cout << "Tus puntos fueron " << jpoints[i] << endl;
            } else {
                cout << "Ganaste con la mano " << i + 1 << " con " << jpoints[i]
                     << " puntos" << endl;
            }
        } else if (jpoints[i] == dealerpoints) {
            cout << "Emapte" << endl;
            cout << "Puntos dealer: " << dealerpoints << endl;
            cout << "Tus puntos: " << jpoints[i] << endl;
        } else if (jpoints[i] > dealerpoints) {
            cout << "Ganaste con la mano " << i + 1 << " con " << jpoints[i]
                 << " puntos" << endl;
        } else {
            cout << "El dealer ha ganado con " << dealerpoints
                 << "puntos para la mano " << i + 1 << endl;
            cout << "Tus puntos fueron " << jpoints[i] << endl;
        }
    }
    this_thread::sleep_for(chrono::milliseconds(750));
}

void mostrarManos(jugador *p, jugador *comp) {
    cout << "Cartas de tus manos:" << endl;

    for (int i = 0; i < p->nmanos; i++) {
        cout << "Cartas de la mano " << i + 1 << "\n|";
        for (int j = 0; j < p->sizes[i]; j++) {
            cout << p->manos[i][j] << '|';
        }
    }
    cout << endl;
    cout << "Cartas del dealer" << endl;
    cout << "|x|";
    for (int i = 1; i < comp->sizes[0]; i++) {
        cout << comp->manos[0][i] << "|";
    }
    cout << endl;
}

bool turnoJ(deck *juego, jugador *p, jugador *comp) {
    mostrarManos(p, comp);
    bool tom = false;
    if (p->nmanos > 1) {
        cout << "Si deseas pedir una carta, ingresa el numero 1 " << endl;
        for (int i = 0; i < p->nmanos; i++) {
            cout << "pedir para la mano " << i + 1 << endl;
            int p2;
            cin >> p2;
            if (p2 == 1) {
                p->add(i, juego->take());
                tom = true;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(250));
        system("cls");
        mostrarManos(p, comp);
    } else {
        cout << "Si deseas pedir una carta, ingresa en numero 1" << endl;
        int p2;
        cin >> p2;
        if (p2 == 1) {
            p->add(0, juego->take());
            tom = true;
        }
        this_thread::sleep_for(chrono::milliseconds(250));
        system("cls");
        mostrarManos(p, comp);
    }
    if (!tom) {
        terminar(juego, p, comp);
        return true;
    }
    return false;
}

bool turnoC(deck *juego, jugador *comp, jugador *p) {
    if (comp->maxpoints() < 17) {
        comp->add(0, juego->take());
        return false;
    }
    if (comp->maxpoints() == 21) {
        cout << "El dealer ha ganado con 21 puntos " << endl;
        return true;
    }
    return false;
}

export namespace blackjack {
    void run() {
        srand(time(NULL));
        deck *juego = new deck();
        jugador *p1 = new jugador();
        jugador *comp = new jugador();

        system("cls");
        cout << "Bienvenido a BlackJack" << endl;
        cout << "Cargando..." << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");

        // repartir cartas
        p1->add(0, juego->take());
        comp->add(0, juego->take());
        comp->add(0, juego->take());
        int n = 1;
        while (p1->sizes[0] == 1 && n == 1) {
            p1->add(0, juego->take());
            mostrarManos(p1, comp);
            if (p1->manos[0][0] == p1->manos[0][1]) {
                cout << "Si desea dividir sus cartas en " << p1->nmanos + 1
                     << " manos, ingrese 1" << endl;
                cin >> n;
                if (n == 1) {
                    p1->divideHands();
                }
            }
            if (p1->nmanos > MAX_SPLIT)
                break;
            system("cls");
        }
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
        while (true) {
            if (turnoJ(juego, p1, comp))
                break;
            if (turnoC(juego, comp, p1))
                break;

            this_thread::sleep_for(chrono::milliseconds(500));
            system("cls");
        }
    }
}