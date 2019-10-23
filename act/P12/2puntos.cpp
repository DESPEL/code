#include "2puntos.hpp"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;


istream &operator >> (istream &in, punto2d &container) {
    cout << "Ingrese la coordenada x del punto " << endl;
    cin >> container.x;
    cout << "Ingrese la coordenada y del punto" << endl;
    cin >> container.y;
    return in;
};

istream &operator >> (istream &in, punto3d &container) {
    cout << "Ingrese la coordenada x del punto " << endl;
    cin >> container.x;
    cout << "Ingrese la coordenada y del punto" << endl;
    cin >> container.y;
    cout << "Ingrese la coordenada z del punto" << endl;
    cin >> container.z;
    return in;
};

namespace puntos {

string ecuacion(punto2d p1, punto2d p2) {
    float m = (p2.y - p1.y) / (p2.x - p1.x);
    float b = p1.y - (m * p1.x);
    return to_string(m) + "x + " + to_string(b);
}

float distance(punto2d p1, punto2d p2) {
    return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

float distance(punto3d p1, punto3d p2) { 
    return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2) + pow((p2.z - p1.z), 2));
}
}  // namespace puntos
