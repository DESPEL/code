// Genetic algorithm implementation
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct coord {
    coord(int px, int py) { x = px, y = py; }
    coord() {}
    int x, y;
};

int random(int min, int max) { return min + (rand() % (max - min + 1)); }

coord generateGene(int nqueens) {
    return (coord(random(0, nqueens - 1), random(0, nqueens - 1)));
}

std::vector<coord> generateIndividual(int nqueens) {
    std::vector<coord> individual(nqueens);
    for_each(begin(individual), end(individual),
             [&](coord &val) { val = generateGene(nqueens); });
    return individual;
}

void mutate(std::vector<coord> &individual) {
    individual[random(0, individual.size() - 1)] =
        generateGene(individual.size());
}

float performance(int nqueens, vector<coord> &individual) {
    std::vector<vector<bool>> queens(nqueens,
                                     std::vector<bool>(nqueens, false));
    int bad = 0;
    for (coord &gene : individual) {
        queens[gene.x][gene.y] = true;
    }
    for (coord &gene : individual) {
        for (int i = 0; i < nqueens; i++) {
            if (queens[gene.x][i] && i != gene.y) {
                bad++;
                continue;
            }
            if (queens[i][gene.y] && i != gene.y) {
                bad++;
                continue;
            }
            if (gene.x + i < nqueens && gene.y + i < nqueens &&
                queens[gene.x + i][gene.y + i]) {
                bad++;
                continue;
            }
            if (gene.x - i >= 0 && gene.y - i >= 0 &&
                queens[gene.x - i][gene.y - i]) {
                bad++;
                continue;
            }
            if (gene.x - i >= 0 && gene.y + i < nqueens &&
                queens[gene.x - i][gene.y + i]) {
                bad++;
                continue;
            }
            if (gene.x + i < nqueens && gene.y - i >= 0 &&
                queens[gene.x + i][gene.y - i]) {
                bad++;
                continue;
            }
        }
    }
    return (nqueens - bad) / nqueens;
}

std::vector<std::vector<coord>> generatePopulation(int size, int boardSize) {
    std::vector<std::vector<coord>> population(size);
    for_each(begin(population), end(population),
             [&](std::vector<coord> &individual) {
                 individual = generateIndividual(boardSize);
             });
    
}

// TODO: reproduce, derive population, generate individual, generate population,
// loop solver

int main() {
    int boardSize;
    cin >> boardSize;
}