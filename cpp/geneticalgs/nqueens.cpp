// Genetic algorithm implementation
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

const float mutationRatio = 0.10;
const float preserveBest = 0.50;
const float preverveRandom = 0.30;
const int popSize = 50;

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
    std::vector<std::vector<bool>> queens(nqueens,
                                          std::vector<bool>(nqueens, false));
    int bad = 0;
    for (coord &gene : individual) {
        queens[gene.x][gene.y] = true;
    }
    // BUG DOWN HERE
    for (coord &gene : individual) {
        for (int i = 0; i < nqueens; i++) {
            if (queens[gene.x][i] && i != gene.x) {
                // std::cout << "1";
                bad++;
                break;
            }
            if (queens[i][gene.y] && i != gene.y) {
                // std::cout << "2";
                bad++;
                break;
            }
            if (gene.x + i < nqueens && gene.y + i < nqueens &&
                gene.x + i != gene.x && gene.y + i != gene.y &&
                queens[gene.x + i][gene.y + i]) {
                // std::cout << "3";
                bad++;
                break;
            }
            if (gene.x - i >= 0 && gene.y - i >= 0 && gene.x - i != gene.x &&
                gene.y - i != gene.y && queens[gene.x - i][gene.y - i]) {
                // std::cout << "4";
                bad++;
                break;
            }
            // possible
            if (gene.x - i >= 0 && gene.y + i < nqueens &&
                gene.x - i != gene.x && gene.y + i != gene.y &&
                queens[gene.x - i][gene.y + i]) {
                // std::cout << "5";
                bad++;
                break;
            }
            if (gene.x + i < nqueens && gene.y - i >= 0 &&
                gene.x + i != gene.x && gene.y - i != gene.y &&
                queens[gene.x + i][gene.y - i]) {
                // std::cout << "6";
                bad++;
                break;
            }
        }
    }
    return (float)(nqueens - bad) / nqueens;
}

std::vector<std::vector<coord>> generatePopulation(int size, int boardSize) {
    std::vector<std::vector<coord>> population(size);
    for_each(begin(population), end(population),
             [&](std::vector<coord> &individual) {
                 individual = generateIndividual(boardSize);
             });
    return population;
}

std::vector<coord> reproduce(std::vector<coord> &parent,
                             std::vector<coord> &mother) {
    int idx = random(0, parent.size() - 1);
    std::vector<coord> child;
    child.insert(begin(child), begin(parent), begin(parent) + idx);
    child.insert(begin(child), begin(mother) + idx, end(mother));
    return child;
}

std::vector<std::vector<coord>> derivePopulation(
    std::vector<std::vector<coord>> &parent) {
    struct association {
        int idx;
        float performance;
    };
    std::vector<association> performances(parent.size());
    int idx = 0;
    float (*perffnc)(int, std::vector<coord> &) = performance;
    for_each(begin(performances), end(performances),
             [&idx, &parent, &perffnc](association &val) {
                 val.idx = idx;
                 val.performance = perffnc(parent[idx].size(), parent[idx]);
                 idx++;
             });
    sort(begin(performances), end(performances),
         [](const association &v1, const association &v2) {
             return v1.performance > v2.performance;
         });

    std::vector<std::vector<coord>> result;
    std::vector<bool> selected(parent.size(), false);

    for (int i = 0; i < parent.size() * preserveBest; i++) {
        result.push_back(parent[performances[i].idx]);
        selected[i] = true;
    }

    for (int i = 0; i < parent.size() * preverveRandom; i++) {
        int pos = random(0, parent.size() - 1);
        while (selected[pos]) pos = random(0, parent.size() - 1);
        selected[pos] = true;
        result.push_back(parent[performances[pos].idx]);
    }

    while (result.size() < parent.size()) {
        int idx1 = random(0, result.size() - 1);
        int idx2 = random(0, result.size() - 1);
        result.push_back(reproduce(result[idx1], result[idx2]));
    }

    for (int i = 0; i < result.size(); i++) {
        if (random(0, 100) < ceil(mutationRatio * 100))
            mutate(result[i]);
    }
    return result;
}
// loop solver

int main() {
    int boardSize;
    std::cin >> boardSize;
    std::vector<vector<coord>> reinas = generatePopulation(popSize, boardSize);
    while (performance(boardSize, reinas[0]) != 1) {
        std::cout << performance(boardSize, reinas[0]) << '\n';
        reinas = derivePopulation(reinas);
    }
    std::vector<std::vector<bool>> mapa(boardSize,
                                        std::vector<bool>(boardSize, false));
    for (coord &pos : reinas[0]) {
        std::cout << "x: " << pos.x << "y: " << pos.y << '\n';
        mapa[pos.x][pos.y] = true;
    }
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            std::cout << mapa[i][j] << ' ';
        }
        std::cout << '\n';
    }
}