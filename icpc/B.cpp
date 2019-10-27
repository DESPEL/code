#include <iostream>
#include <map>
#include <tuple>
#include <cmath>

using namespace std;

struct coord {
    coord() {}
    coord(double px, double py) {
        x = px;
        y = py;
    }
    double x;
    double y;
}

int main () {
    int n;
    cin >> n;
    vector<coord> elementos(n);
    coord temp;
    for (int i = 0; i < n; i++) {
        cin >> temp.x >> temp.y;
        elementos[i] = temp;
    }
    
    map<tuple<coord,coord,coord,coord, double>, int> posibles;
    coord c1, c2;
    for (int i = 0 ; i < n; i++) {
        c1 = elementos[i];
        for (int j = i + 1; j < n; j++) {
            c2 = elementos[j];
            if (c1.x == c2.x) continue;
            if (c1.y == c2.y) continue;
            coord pm = {(c1.x + c2.x) / 2, (c1.y + c2.y) / 2};
            double m1 = ((c2.y - c1.y) / (c2.x - c1.x))
            double m2 = 1 / m1;
            coord cambio = {abs(c1.x - pm.x), abs(c1.y - pm.y)};

        }
    }

}