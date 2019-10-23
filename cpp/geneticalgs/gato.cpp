#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

int random(int min, int max) {
    return min + (rand() %(min - max + 1));
}

float prob () {
    return (float)random(1,100) / 100;
}

struct AI {
    float tiros[3] = {0, 0, 0};
    int galletas;
};

int comer (AI ) {

}

int main () {
    int galletas = 21;

    AI jug1;
    jug1.tiros[0] = prob();
    jug1.tiros[1] = prob();
    jug1.tiros[2] = prob();
    AI jug2;
    jug2.tiros[0] = prob();
    jug2.tiros[1] = prob();
    jug2.tiros[2] = prob();

    for (int i = 0; i < 3; i++) {
        std::cout << jug1.tiros[i] << ' ';
    }
    std::cout << '\n';
    for (int i = 0; i < 3; i++) {
        std::cout << jug2.tiros[i] << ' ';
    }
    std::cout << '\n';

}