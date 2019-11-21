#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <thread>
#include <chrono>

using namespace std;

int random(int min, int max) { return min + (rand() % (max - min + 1)); }
string cs = "PCDT", cs2 = "A234567891JQK";
void randomize(vector<pair<int, int>>& vals) {
	for (size_t i = 0; i < vals.size(); i++) {
		pair<int, int> t = vals[i];
		int idx = random(0, vals.size() - 1);
		vals[i] = vals[idx], vals[idx] = t;
	}
}
int contar(const vector<pair<int, int>>& jugador) {
	int puntos[7]{ 0 };
	int* veces = new int[13]{ 0 };
	for (const pair<int, int>& c : jugador)
		veces[c.first]++;
	for (int i = 0; i < 13; i++)
		puntos[veces[i]]++;
	return puntos[2] * 2 + puntos[3] * 3 + puntos[4] * 4;
}
pair<int, int> take(vector<pair<int, int>>& d) {
	pair<int, int> t = d.back();
	d.pop_back();
	return t;
}
void mostrarCartas(vector<pair<int, int>>& j) {
	for (const pair<int, int>& c : j)cout << ((c.first == 10) ? "10" : string(1, cs2[c.first - 1])) << cs[c.second] << ' ';
}
int main() {
	srand(time(NULL));
	int n, imax = 0, vmax = 0, run = 1, p = 0;
	vector<pair<int, int>> deck, pool;
	vector<int> ganadores;
	for (int i = 0; i < 4; i++)
		for (int j = 1; j <= 13; j++)
			deck.push_back(make_pair(j, i));
	randomize(deck);
	cout << "Ingrese la cantidad de jugadores (2 - 6)" << '\n';
	for (cin >> n; n < 2 || n > 6; cout << "Ingrese una cantidad de jugadores valida" << '\n', cin >> n);
	vector<vector<pair<int, int>>> jugadores(n);
	for (vector<pair<int, int>>& c : jugadores)
		for (int i = 0; i < 5; i++)
			c.push_back(take(deck));
	for (int i = 0; run == 1 || (ganadores.size() > 0 && i != ganadores[0]); i++, i %= n) {
		if (deck.size() == 0) {
			cout << "Se han acabado las cartas del pool, revolviendo" << '\n';
			this_thread::sleep_for(chrono::milliseconds(500));
			deck = pool;
			pool.clear();
			randomize(deck);
		}
		system("cls");
		cout << "Turno del jugador " << i + 1 << '\n' << "Cartas: ";
		mostrarCartas(jugadores[i]);
		cout << '\n';
		if (pool.size() != 0) {
			cout << "La carta del pool es: " << ((pool.back().first == 10) ? "10" : string(1, cs2[pool.back().first - 1])) << cs[pool.back().second] << '\n';
			cout << "Ingrese 1 si desea una carta del pool" << '\n';
			cin >> p;
		}
		else cout << "Como no habian cartas en el pool, se le dio una del deck" << '\n';
		if (p == 1) jugadores[i].push_back(take(pool));
		else jugadores[i].push_back(take(deck));
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
		for (cin >> p; p < 1 || p > 6; cout << "Ingrese un indice de carta valido" << '\n', cin >> p);
		pool.push_back(jugadores[i][p - 1]);
		jugadores[i].erase(jugadores[i].begin() + p - 1);
	}
	system("cls");
	for (int i = 0; i < ganadores.size(); i++) {
		int suma = accumulate(begin(jugadores[ganadores[i]]), end(jugadores[ganadores[i]]), 0, [&](int a, pair<int, int> b) {return a + b.first; });
		if (suma > vmax) vmax = suma, imax = ganadores[i];
	}
	cout << "El jugador " << imax + 1 << " ha ganado" << '\n';
	cin >> p;
}