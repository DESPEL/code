#include <iostream>
#include <string>
#include <random>
#include <io.h>
#include <chrono>
#include <thread>
#define pool stack<card> // simular objeto de pool

using namespace std;

wstring_view symbols[] = {L"♥", L"♦", L"♣", L"♠"};

inline int random(int min, int max) {return min + (rand() % (max - min + 1));}

// Permitir el output de los símbolos de las cartas
template <typename T>
void wprint(T str) {
	int t =_setmode(_fileno(stdout), 0x20000);
	wcout << str;
	t = _setmode(_fileno(stdout), 0x4000);
}

template <typename T>
struct node {
	node() {}
	node(T v) { val = v; }
	T val = T();
	node<T>* next = nullptr;
	node<T>* prev = nullptr;
};

template <typename T>
struct stack {
	stack() {}
	node<T>* t = new node<T>();
	int sz = 0;

	void insert(T val) {
		node<T>* n = new node<T>(val);
		n->next = t, t = n, sz++;
	}

	void pop() {
		if (size() == 0) throw underflow_error("Intento de borrado en stack vacio");
		node<T>* temp = t;
		t = t->next;
		delete temp;
		sz--;
	}

	T top() const {
		if (size() == 0) throw underflow_error("Intento de consulta en stack vacio");
		return t->val;
	}

	int size() const { return sz; }
};

template <typename T>
struct circularList {
	node<T>* head = nullptr, *last = nullptr, *act = nullptr;
	int sz = 0;
	
	void insert(T val) {
		if (head == nullptr) {
			head = new node<T>(val);
			last = head;
			last->next = head;
			last->prev = head;
			act = head;
		} else {
			last->next = new node<T>(val);
			last->next->prev = last, last = last->next, last->next = head;
		}
		sz++;
	}

	void next() {act = act->next;}
	void reset() {act = head;}
	int size() const { return sz; }

	void pop() {
		if (size() == 0)
			throw underflow_error("Intento de borrado en lista circular vacia");
		if (size() == 1) {
			delete head;
		} else {
			if (act == last)
				act = act->prev;
			last = last->prev;
			delete last->next;
			last->next = head;
		}
		sz--;
	}

	T actual() const {
		if (size() == 0) throw underflow_error("Intento de consulta en lista circular vacia");
		return act->val;
	}
};

struct card {
	card() {}
	card(int v, int p, bool c) {
		valor = v, palo = p, color = c;
	}
	int valor{};
	int palo{};
	bool color{};
};

struct deck {
	stack<card> cartas;
	int nbarajas;
	mt19937 gen;
	uniform_int_distribution<int> rng;

	deck(int n = 1) {
		gen.seed(random_device()());
		uniform_int_distribution<int> t(0, (52 * n) - 1);
		rng = t;
		nbarajas = n;
	}

	void generate() {
		card *temp = new card[nbarajas * 52]();

		for (int i = 0; i < nbarajas; i++) 
			for (int j = 0; j < 13; j++) 
				for (int k = 0; k < 4; k++) 
					temp[i * 52 + j * 4 + k] = card(j + 1, k, k < 2);

		for (int i = 0; i < nbarajas * 52; i++) {
			int idx = rng(gen);
			card t = temp[i];
			temp[i] = temp[idx];
			temp[idx] = t;
		}
		for (int i = 0; i < nbarajas * 52; i++) 
			cartas.insert(temp[i]);

		delete[] temp;
	}

	card top() { return cartas.top(); }
	void pop() { cartas.pop(); }
	int size() { return cartas.size(); }
};

struct jugador {
	bool comp;
	card cartas[6];
	string name;
	int sz = 5;
	jugador(string n, bool c = false) {name = n, comp = c;}

	bool add(card carta) {
		if (sz == 6) return false;

		cartas[5] = carta;
		sz = 6;
		return true;
	}
	
	bool drop(int pos) {
		if (sz < 6) return false;
		for (int i = pos; i < sz - 1; i++)
			cartas[i] = cartas[i + 1];
		sz = 5;
		return true;
	}

	int contar() {
		// contar pares y los de 3
		int conteo[13]{ 0 };
		for (int i = 0; i < sz; i++)
			conteo[cartas[i].valor - 1]++;
		int pares = 0, triples = 0, poker = 0;
		// buscar poker / contar triples y pares
		for (const int& val : conteo)
			if (val == 2) pares++;
			else if (val == 3) triples++;
			else if (val == 4) poker++;
		if (pares == 3) return 6;
		if (triples == 2) return 6;
		if (pares == 1 and triples == 1) return 5;
		if (poker == 1 and pares == 1) return 6;
		if (poker == 1) return 5;
	
		// buscar escalera
		int cons = 0, consmax = 0, last;
		for (int i = 0; i < 13; i++) {
			if (conteo[i] == 1) {
				cons++;
				if (cons > consmax) consmax = cons;
				last = i;
			} else
				cons = 0;
		}
		if (consmax >= 5) return consmax;
		return pares * 2 + triples * 3;
	}

	int unused() {
		pair<int,int> conteo[13]{make_pair(0,0)};
		for (int i = 0; i < sz; i++) {
			conteo[cartas[i].valor - 1].second++;
			conteo[cartas[i].valor - 1].first = i;
		}
		for (int i = 0; i < 13; i++) 
			if (conteo[i].second >= 1)
				return conteo[i].first;
		return -1;
	}

	bool pickpool(int tval) {
		for (int i = 0; i < sz; i++)
			if (cartas[i].valor == tval) return true;
		return false;
	}

	int size() {return sz;}
};

struct juego {
	circularList<jugador*> jugadores;
	stack<jugador*> ganadores;
	deck baraja;
	pool p;

	juego(int r, int c = 0, int n = 1) {
		int d = 0;
		for (int i = 0; i < r; i++) 
			jugadores.insert(new jugador(to_string(++d)));
		for (int i = 0; i < c; i++)
			jugadores.insert(new jugador(to_string(++d), true));
		baraja = deck(n);
		baraja.generate();
	}

	void repartir() {
		do {
			for (int i = 0; i < 5; i++) {
				jugadores.actual()->cartas[i] = baraja.top();
				baraja.pop();
			}
			jugadores.next();
		} while (jugadores.head->val != jugadores.actual());
	}

	void reshuffle() {
		card* temp = new card[p.size()];
		int tsz = p.size();
		for (int i = 0; p.size() > 0; i++) {
			temp[i] = p.top();
			p.pop();
		}
		for (int i = 0; i < tsz; i++) {
			int idx = random(0, tsz - 1);
			card tval = temp[i];
			temp[i] = temp[idx], temp[idx] = tval;
		}
		for (int i = 0; i < tsz; i++)
			baraja.cartas.insert(temp[i]);
	}

	jugador* end() {
		jugador* g = nullptr;
		int vmax = 0;
		while (ganadores.size() > 0) {
			int suma = 0;
			jugador* actual = ganadores.top();
			ganadores.pop();
			for (int i = 0; i < actual->size(); i++) 
				suma += (actual->cartas[i].valor == 1)? 14 : actual->cartas[i].valor;
			if (suma >= vmax) {
				vmax = suma;
				g = actual;
			}
		}
		return g;
	}

};

void mostrarCarta(const card& c) {
	if (c.valor == 1) cout << "A";
	else if (c.valor == 11) cout << "J";
	else if (c.valor == 12) cout << "Q";
	else if (c.valor == 13) cout << "K";
	else cout << c.valor;
	wprint(symbols[c.palo]);
}

void mostrarCartas(const jugador *j) {
	for (int i = 0; i < j->sz; i++) {
		mostrarCarta(j->cartas[i]);
		cout << ((i < (j->sz - 1)) ? ", " : " ");
	}
	cout << '\n';
}

void run() {
	int n = 1, c = 0, nb = 1;
	cout << "Bienvenido al juego de gofish" << '\n';
	cout << "Ingrese la cantidad de jugadores (2 - n)"<< '\n';
	cout << "Para jugar con mas de 6 jugadores se necesita que ingrese el numero de barajas" << '\n';
	cin >> n;
	while (n < 2) {
		cout << "Ingrese un valor mayor a 2" << '\n';
		cin >> n;
	}
	if (n > 6) {
		cout << "Ingrese la cantidad de barajas (" << (n + n%6) / 6 << " - n)" << '\n';
		cin >> nb;
		while (nb < n / 6) {
			cout << "Ingrese un valor mayor a " << (n+n%6) / 6 << '\n';
			cin >> nb;
		}
	}

	cout << "Ingrese la cantidad de jugadores que manejara la computadora (0 - " << n - 1 << ")" << '\n';
	cin >> c;
	while (c < 0 || c > n - 1) {
		cout << "Ingrese un valor entre 0 y " << n - 1 << " inclusive" << '\n';
		cin >> c;
	}

	system("cls");
	cout << "Iniciando..." << '\n';
	this_thread::sleep_for(chrono::milliseconds(750));
	system("cls");
	
	juego j(n - c, c, nb);
	j.repartir();
	bool first = true;
	jugador* ganador = nullptr;
	for (int turnos = 0; ; turnos++) {
		if (turnos == 0) {
			j.jugadores.actual()->add(j.baraja.top());
			j.baraja.pop();
		}
		do {
			jugador* actual = j.jugadores.actual();

			if (actual == ganador) {
				cout << "La vuelta para ganar ha terminado " << '\n';
				jugador* gr = j.end();
				cout << "El jugador " << gr->name << " ha ganado" << '\n';
				return;
			}

			if (!actual->comp) {
				cout << "Cartas del jugador " << actual->name << ":" << '\n';
				mostrarCartas(actual);
				if (j.p.size() > 0) {
					cout << "Carta del pool: ";
					mostrarCarta(j.p.top());
					cout << '\n';
					cout << "Carta de la baraja: " << "x" << '\n';
					cout << "Ingrese 1 si desea tomar la carta del pool" << '\n';
					cin >> n;
				} else if(!first) {
					cout << "Como no habian mas cartas en el pool, se te dio una de la baraja" << '\n';
					this_thread::sleep_for(chrono::milliseconds(500));
				}
				system("cls");
				if (n == 1 && j.p.size() >= 1) {
					actual->add(j.p.top());
					j.p.pop();
				} else {
					actual->add(j.baraja.top());
					j.baraja.pop();
				}
				cout << "Cartas del jugador " << actual->name << '\n';
				mostrarCartas(actual);
				int maxjug = actual->contar();
				cout << "Su mejor jugada es de " << maxjug << " cartas" << '\n';
				if (maxjug == 6) {
					system("cls");
					cout << "El jugador " << actual->name << " ha ganado" << '\n';
					return;
				}
				if (maxjug == 5 && ganador == nullptr) {
					int tmp;
					cout << "Tiene una jugada de 5 cartas, ingrese 1 si desea bajar su jugada" << '\n';
					cin >> tmp;
					if (tmp == 1) {
						cout << "El jugador " << actual->name << " ha bajado sus carats" << '\n';
						cout << "El juego se acaba en la siguiente vuelta" << '\n';
						ganador = actual;
					}
					j.ganadores.insert(actual);
				} else if (maxjug == 5) {
					cout << "Tienes una jugada de 5 cartas, automaticamente te bajas (ultima vuelta)" << '\n';
					j.ganadores.insert(actual);
				}
				cout << "Elija una carta para dejar en el pool (1 - 6)" << '\n';
				cin >> n;
				while (n < 1 || n > 6) {
					cout << "Ingrese un numero entre 1 y 6 inclusive" << '\n';
					cin >> n;
				}
				j.p.insert(actual->cartas[n - 1]);
				actual->drop(n - 1);

				system("cls");
			}
			else {
				cout << "La computadora (jugador " << actual->name << ") esta tirando" << '\n';
				bool fpool = (j.p.size() > 0) ? actual->pickpool(j.p.top().valor) : false;
				if (fpool) {
					actual->add(j.p.top()); j.p.pop();
				} else {
					actual->add(j.baraja.top()); j.baraja.pop();
				}
				int maxjug = actual->contar();
				if (maxjug == 6) {
					system("cls");
					cout << "El jugador " << actual->name << " ha ganado" << '\n';
					return;
				}
				if (maxjug == 5 && ganador == nullptr) {
					j.ganadores.insert(actual);
					cout << "El jugador " << actual->name << " ha bajado sus cartas" << '\n';
					cout << "El juego se acaba en la siguiente vuelta" << '\n';
					ganador = actual;
				} else if (maxjug == 5) {
					cout << "Ha bajado " << actual->name << " sus cartas";
					j.ganadores.insert(actual);
				}
				int tdrp = actual->unused();
				j.p.insert(actual->cartas[tdrp]);
				actual->drop(tdrp);
				this_thread::sleep_for(chrono::milliseconds(1000));
				system("cls");
			}

			if (j.baraja.size() == 0) {
				system("cls");
				cout << "La baraja se ha terminado" << '\n';
				cout << "Mezclando las cartas del pool" << '\n';
				j.reshuffle();
				this_thread::sleep_for(chrono::milliseconds(500));
			}
			j.jugadores.next();
			first = false;
		} while (j.jugadores.actual() != j.jugadores.head->val);
	}
	return;
}

int main() {
	srand(random_device()());
	int n;
	while (true) {
		run();
		this_thread::sleep_for(chrono::milliseconds(1000));
		system("cls");
		cout << "Ingrese 1 si desea jugar de nuevo" << '\n';
		cin >> n;
		if (n != 1) break;
	}
	return 0;
}