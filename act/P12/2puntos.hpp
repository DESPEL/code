#pragma once
#include <string>
#include <iostream>

using namespace std;

struct punto2d {
    float x, y;
};
istream &operator >> (istream &in, punto2d &container);
struct punto3d {
    float x, y, z;
};
istream &operator >> (istream &in, punto3d &container);

namespace puntos {

std::string ecuacion(punto2d p1, punto2d p2);
float distance(punto2d p1, punto2d p2);
float distance(punto3d p1, punto3d p2);

}  // namespace puntos