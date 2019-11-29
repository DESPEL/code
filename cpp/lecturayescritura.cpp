#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    // escribir archivo
    ofstream escritura;
    escritura.open("archivo1");
    // funciona como un cout // el archivo se genera automaticamente
    escritura << "asdfasdf";
    // cerrar el fstraem
    escritura.close();

    // lectura
    ifstream lectura;
    lectura.open("archivo1");
    string texto;
    // leer el priemr conjunto de letras hasta el espacio, funciona como un cin
    lectura >> texto;

    // ejemplo para guardar variables y cosas asi
    map<string, string> variables;
    // guardar variables en el "map", es como un array, pero que peudes acceder
    // a cosas con string de posicion
    variables["variable1"] = "quiero guardar esto";
    variables["variable2"] = "quiero guardar esta otra cosa";

    // pasar todas las variables al archivo
    ofstream guardar;
    guardar.open("variables");
    for (pair<const string, string>& variable : variables) {
        guardar << variable.first << "~" << variable.second << '\n';
    }
    // las variables quedan guardadas en un txt, separadas por un '~'
    guardar.close();
    // leer variables
    ifstream leer;
    // abrir archivo donde se guardaron
    leer.open("variables");
    string nombre, valor;
    // lugar para guardar las variable
    map<string, string> vars;
    // leer el archivo
    while (getline(leer, nombre, '~') && getline(leer, valor)) {
        cout << nombre;
        vars[nombre] = valor;
    }
    leer.close();
    // imprimir valores
    for (pair<const string, string>& variable : vars) {
        cout << variable.first << ":" << variable.second << '\n';
    }
}