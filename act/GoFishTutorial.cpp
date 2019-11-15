#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <thread>
#include <chrono>

using namespace std;

struct carta {
	carta(int pv, int pp) {
		p = pp, v = pv;
	}
	int p;
	int v;
};

struct jugador {
	vector<carta> cartas;
};

// generar numeros aleatorios en un rango
int random(int min, int max) {
	return min + (rand() % (max - min + 1));
}

// string para imprimir cartas
string cs = "PCDT", cs2 = "A234567891JQK";
int contar(jugador& jugador) {
	int puntos[7]{ 0 };
	int* veces = new int[13]{ 0 };
	for (carta& c : jugador.cartas)
		veces[c.v]++;
	for (int i = 0; i < 13; i++)
		puntos[veces[i]]++;
	return puntos[2] * 2 + puntos[3] * 3 + puntos[4] * 4;
}
carta take(vector<carta>& d) {
	carta t = d.back();
	d.pop_back();
	return t;
}


void mostrarCartas(jugador& j) {
	// imprimir cartas de acuerdo a sus caracteristicas
	for (carta c : j.cartas) {
			cout << ((c.v == 10) ? "10" : string(1, cs2[c.v - 1])) << cs[c.p] << ' ';
	}
}
int main() {
	srand(time(NULL));
	int n, imax = 0, vmax = 0, run = 1, p = 0;
	vector<carta> deck, pool;
	vector<int> ganadores;

	// generar mazo (deck)
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 13; j++)
			deck.push_back(carta(j, i));
	}
	// revolver el mazo (deck)
	for (int i = 0; i < deck.size(); i++) {
		carta t = deck[i];
		int idx = random(0, deck.size() - 1);
		deck[i] = deck[idx], deck[idx] = t;
	}

	// pedir la cantidad de jjugadores
	cout << "Ingrese la cantidad de jugadores (2 - 6)" << '\n';
	// verificar la entrada (opcional)
	for (cin >> n; n < 2 || n > 6; cout << "Ingrese una cantidad de jugadores valida" << '\n', cin >> n);

	// crear jugadores
	vector<jugador> jugadores(n);

	// repartir 5 cartas a cada jugador
	for (jugador& j : jugadores) {
		for (int i = 0; i < 5; i++)
			j.cartas.push_back(take(deck));
	}

	// correr el juego
	for (int i = 0; run == 1 || (ganadores.size() > 0 && i != ganadores[0]); i++, i %= n) {
		// Si el mazo no tiene cartas, vaciarlo y volverlo a llenar
		if (deck.size() == 0) {
			cout << "Se han acabado las cartas del pool, revolviendo" << '\n';
			this_thread::sleep_for(chrono::milliseconds(500));
			deck = pool;
			pool.clear();
			for (int i = 0; i < deck.size(); i++) {
				carta t = deck[i];
				int idx = random(0, deck.size() - 1);
				deck[i] = deck[idx], deck[idx] = t;
			}
		}

		// imprimir el turno del jugador y limpiar consola
		system("cls");
		cout << "Turno del jugador " << i + 1 << '\n' << "Cartas: ";
		mostrarCartas(jugadores[i]);
		cout << '\n';
		// preguntar si quiere carta del pool o del deck
		if (pool.size() != 0) {
			cout << "La carta del pool es: " << ((pool.back().v == 10) ? "10" : string(1, cs2[pool.back().v - 1])) << cs[pool.back().p] << '\n';
			cout << "Ingrese 1 si desea una carta del pool" << '\n';
			cin >> p;
		}
		else cout << "Como no habian cartas en el pool, se le dio una del deck" << '\n';
		if (p == 1) { 
			jugadores[i].cartas.push_back(take(pool)); 
		}
		else {
			jugadores[i].cartas.push_back(take(deck));
		}

		// imprimir cartas luego de tomarlas de donde sea y limpiar consola
		system("cls");
		cout << "Las cartas del jugador " << i + 1 << "son: \n";
		mostrarCartas(jugadores[i]);
		cout << '\n' << "Su mejor jugada es de " << contar(jugadores[i]) << " cartas" << '\n';
		if (contar(jugadores[i]) == 6) {
			cout << "Tiene una jugada de 6 cartas, ha ganado" << '\n';
			return 0;
		}
		else if (contar(jugadores[i]) == 5) {
			cout << "Tiene una jugada de 5 cartas, ingrese 1 si desea bajarse" << '\n';
			cin >> p;
			if (p == 1) {
				cout << "El juego se acaba en la siguiente vuelta" << '\n';
				ganadores.push_back(i);
				run = 0;
			}
		}
		cout << "Elija una carta para dejar en el pool (1 - 6)" << '\n';
		// no es recomendable utilizar for de 1 linea
		for (cin >> p; p < 1 || p > 6; cout << "Ingrese un indice de carta valido" << '\n', cin >> p);
		pool.push_back(jugadores[i].cartas[p - 1]);
		// un poco de iteradores, se puede hacer de otras maneras, pero esta es más sencilla
		jugadores[i].cartas.erase(jugadores[i].cartas.begin() + p - 1);
	}
	system("cls");
	
	// buscar el jugador con la suma mas alta
	for (int i = 0; i < ganadores.size(); i++) {
		// si, esta linea de abajo hace cosas graciosas, pero funciona
		int suma = accumulate(begin(jugadores[ganadores[i]].cartas), end(jugadores[ganadores[i]].cartas), 0, [&](int a, carta b) {return a + b.v; });
		if (suma > vmax) vmax = suma, imax = ganadores[i];
	}
	// imprimir el jugador con la mejor jugada
	cout << "El jugador " << imax + 1 << " ha ganado" << '\n';

	// evitar que se cierre la consola
	cin >> p;
}