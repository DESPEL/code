#include <iostream>
#include <vector>
#include <algorithm>

#include "DB.h"
#include "ReconstructDB.cpp"

using namespace std;

bool verificarMarca(const DB& marcas, const string& str) {
	for (const pair<const string, Table> marca : marcas.tables) {
		if (utils::to_lower(marca.first) == utils::to_lower(str))
			return true;
	}
	return false;
}

string getRealStr(const DB& marcas, const string& str) {
	for (const pair<const string, Table> marca : marcas.tables) {
		if (utils::to_lower(marca.first) == utils::to_lower(str))
			return marca.first;
	}
	return "";
}

void crear() {
	string opcion;
	cout << "Ingrese 'usuario' si desea crear un usuario" << '\n';
	cout << "Ingrese 'automovil' si desea crear un automovil" << '\n';
	cin >> opcion;
    opcion.erase(remove(begin(opcion), end(opcion), '\''), end(opcion));
	while (!(opcion == "usuario" || opcion == "automovil")) {
		cout << "Ingrese una opcion valida" << '\n';
		cin >> opcion;
	}
	DB lugar("usuario");

	vector<string> data(lugar.tables[opcion].fields.size());
	cin.ignore(1000, '\n');
	for (const pair<string, int>&campo : lugar.tables[opcion].fields) {
		cout << "Ingrese: " << campo.first << " del " << opcion << '\n';
		getline(cin, data[campo.second - 1]);
	}
	
	if (opcion == "usuario") {
		DB estados("estados");
		string nacionalidad = utils::trim(utils::sanitize(utils::to_lower(data[lugar.tables[opcion].fields["pais de nacimiento"] - 1])));
		while (estados.tables.find(nacionalidad) == end(estados.tables) && nacionalidad != "otro") {
			cout << "Ingrese un estado valido (estados unidos, mexico, otro)" << '\n';
			getline(cin, data[lugar.tables[opcion].fields["pais de nacimiento"] - 1]);
			nacionalidad = utils::trim(utils::sanitize(utils::to_lower(data[lugar.tables[opcion].fields["pais de nacimiento"] - 1])));
		}

		if (utils::to_lower(nacionalidad) != "otro") {
			string estado = data[lugar.tables[opcion].fields["lugar de nacimiento"] - 1];
			string temp;
			for (const char& c : estado) {
				if (c == ',') {
					temp.clear();
				}
				else {
					temp += string(1, c);
				}
			}
			estado = utils::trim(temp);
			//cout << estado;
			while (estados.select(nacionalidad, { {"nombre", estado} }).empty()) {
				cout << "Ese lugar de nacimiento no existe, verifique la entrada" << '\n';
				getline(cin, data[lugar.tables[opcion].fields["lugar de nacimiento"] - 1]);
				estado = data[lugar.tables[opcion].fields["lugar de nacimiento"] - 1];
				temp.clear();
				for (const char& c : estado) {
					if (c == ',') {
						temp.clear();
					}
					else {
						temp += string(1, c);
					}
				}
				estado = utils::trim(temp);
				//cout << estado;
			}

		}
	}
	else {
		DB marcas("marcas");
		string placa = utils::trim(data[lugar.tables[opcion].fields["placas"] - 1]);
		while (placa.size() > 6) {
			cout << "Esa placa no es valida, ingrese una de 6 de longitud" << '\n';
			getline(cin, data[lugar.tables[opcion].fields["placas"] - 1]);
			placa = utils::trim(data[lugar.tables[opcion].fields["placas"] - 1]);
		}

		string marca = utils::trim(data[lugar.tables[opcion].fields["marca"] - 1]);
		while (!verificarMarca(marcas, marca)) {
			cout << "La marca ingresada no existe, ingrese una real" << '\n';
			getline(cin, data[lugar.tables[opcion].fields["marca"] - 1]);
			marca = utils::trim(data[lugar.tables[opcion].fields["marca"] - 1]);
		}
		string linea = utils::trim(data[lugar.tables[opcion].fields["linea"] - 1]);
		while (marcas.select(getRealStr(marcas, marca), { {"nombre", linea} }).empty()) {
			cout << "La linea ingresada no existe, ingrese una existente" << '\n';
			getline(cin, data[lugar.tables[opcion].fields["linea"] - 1]);
			linea = utils::trim(data[lugar.tables[opcion].fields["linea"] - 1]);
		}

		DB colores("colores");
		string color = utils::trim(data[lugar.tables[opcion].fields["color"] - 1]);
		while (colores.select("colores", { {"nombre", color} }).empty()) {
			cout << "Ese color no existe, ingresa uno real (la base de datos contiene 2331 colores)" << '\n';
			getline(cin, data[lugar.tables[opcion].fields["color"] - 1]);
			color = utils::trim(data[lugar.tables[opcion].fields["color"] - 1]);
		}

	}
	cout << opcion << " registrado correctamente" << '\n';
	lugar.write(opcion, data);
	cout << "Apriete una tecla para continuar" << '\n';
	getline(cin, opcion);
}

void consultar() {
	string opcion;
	cout << "Ingrese 'usuario' si desea buscar un usuario" << '\n';
	cout << "Ingrese 'automovil' si desea buscar un automovil" << '\n';
	cin >> opcion;
	opcion.erase(remove(begin(opcion), end(opcion), '\''), end(opcion));
	while (!(opcion == "usuario" || opcion == "automovil")) {
		cout << "Ingrese una opcion valida" << '\n';
		cin >> opcion;
	}
	DB lugar("usuario"); 
	
	vector<string> data(lugar.tables[opcion].fields.size());
	cin.ignore(1000, '\n');
	cout << "Si no desea buscar un campo, solo ingrese 'no'" << '\n';
	for (const pair<string, int>& campo : lugar.tables[opcion].fields) {
		cout << "Ingrese: " << campo.first << " del " << opcion << '\n';
		getline(cin, data[campo.second - 1]);
	}
	for (string& str : data) {
		if (utils::to_lower(utils::trim(str)) == "no") {
			str = "";
		}
	}
	vector<pair<string, string>> busqueda;
	int i = 0;
	for (string& str : data) {
		if (!str.empty()) {
			busqueda.push_back({ lugar.tables[opcion].r_fields[i + 1] ,str });
		}
		i++;
	}
	system("cls");
	vector<vector<string>> res = lugar.select(opcion, busqueda);
	cout << "Resultados:" << "\n";
	if (res.empty()) {
		cout << "Ninguno" << '\n';
	}
	for (vector<string> r : res) {
		cout << "Registro: " << '\n';
		for (int i = 0; i < r.size(); i++) {
			cout << lugar.tables[opcion].r_fields[i + 1] << ": " << r[i] << '\n';
		}
		cout << '\n';
	}
	cout << "Apriete una tecla para continuar" << '\n';
	getline(cin, opcion);
}

int menuPrincipal() {
	cout << "Bienvenido a la base de datos:" << '\n';
	cout << "Al escribir no ingrese tildes o caracteres especiales" << '\n';
	cout << "Ingrese el numero de la opcion de la tarea que desea realizar" << '\n';
	cout << "1) Crear usuario o automovil" << '\n';
	cout << "2) Consultar automoviles de usuario/s" << '\n';
	cout << "3) Salir" << '\n';
	int n;
	cin >> n;
	while (n < 1 || n > 2) {
		cout << "Ingrese una opcion valida" << '\n';
		cin >> n;
	}
	return n;
}

int main() {
	// rebuild() -- descomentar en la primera ejecucion para crear bases de datos y todo eso
	while (true) {
		int opt = menuPrincipal();
		if (opt == 1) {
			system("cls");
			crear();
		} 
		if (opt == 2) {
			system("cls");
			consultar();
		}
		if (opt == 3) {
			break;
		}
		system("cls");
	}
}