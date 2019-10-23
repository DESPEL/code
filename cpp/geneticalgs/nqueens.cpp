// Genetic algorithm implementation -- NO
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <vector>

using namespace std;

const float mutationRatio = 0.05;
const float preserveBest = 0.70;
const float preverveRandom = 0.20;
const int popSize = 20;

struct coord {
    coord(int px, int py) { x = px, y = py; }
    coord() {}
    int x, y;
};

bool findRep(std::vector<coord> &ind) {
    for (int i = 0; i < ind.size(); i++) {
        for (int j = i + 1; j < ind.size(); j++) {
            if (ind[i].x == ind[j].x && ind[i].y == ind[j].y) {
                return true;
            }
        }
    }
    return false;
}

int random(int min, int max) { return min + (rand() % (max - min + 1)); }

coord generateGene(int nqueens) {
    return (coord(random(0, nqueens - 1), random(0, nqueens - 1)));
}

std::vector<coord> generateIndividual(int nqueens) {
    // std::cout << "gi";
    std::vector<coord> individual;
    for (int i = 0; i < nqueens; i++) {
        coord newGene = generateGene(nqueens);
        while (find_if(begin(individual), end(individual), [&](coord &val) {
                   return val.x == newGene.x && val.y == newGene.y;
               }) != end(individual)) {
            newGene = generateGene(nqueens);
        }
        individual.push_back(newGene);
    }
    // std::cout << findRep(individual) << '\n';
    return individual;
}

void mutate(std::vector<coord> &individual) {
    // std::cout << "mut";
    coord newGene = generateGene(individual.size());
    while (find_if(begin(individual), end(individual), [&newGene](coord &el) {
               return el.x == newGene.x && el.y == newGene.y;
           }) != end(individual)) {
        newGene = generateGene(individual.size());
    }
    int index = random(0, individual.size() - 1);
    individual[index] = newGene;
    // std::cout << findRep(individual) << '\n';
}

float performance(int nqueens, vector<coord> &individual) {
    std::vector<std::vector<bool>> queens(nqueens,
                                          std::vector<bool>(nqueens, false));
    int bad = 0;
    for (coord &gene : individual) {
        queens[gene.x][gene.y] = true;
    }
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
    // std::cout << "rep";
    // std::cout << findRep(parent) << findRep(mother);
    int idx = random(0, parent.size() - 1);
    std::vector<coord> child;
    child.insert(begin(child), begin(parent), begin(parent) + idx);
    for (int i = idx; i < mother.size(); i++) {
        if (find_if(begin(child), end(child), [&i, &mother](coord &val) {
                return val.x == mother[i].x && val.y == mother[i].y;
            }) == end(child)) {
            child.push_back(mother[i]);
        } else {
            coord ncoord = generateGene(parent.size());
            while (find_if(begin(child), end(child), [&ncoord](coord &val) {
                       return val.x == ncoord.x && val.y == ncoord.y;
                   }) != end(child)) {
                ncoord = generateGene(parent.size());
            }
            child.push_back(ncoord);
        }
    }
    // std::cout << findRep(child) << '\n';
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
        if (random(0, 100) < 80) {
            result.push_back(reproduce(result[idx1], result[idx2]));
        } else {
            result.push_back(generateIndividual(parent[0].size()));
        }
    }

    for (int i = 0; i < result.size(); i++) {
        if (random(0, 100) < ceil(mutationRatio * 100))
            mutate(result[i]);
    }
    return result;
}

float avgPerf(std::vector<std::vector<coord>> &population) {
    float total = 0;
    for (std::vector<coord> &individual : population) {
        total += performance(individual.size(), individual);
    }
    return total / population.size();
}
int main() {
    int boardSize;
    std::cin >> boardSize;
    std::vector<vector<coord>> reinas = generatePopulation(popSize, boardSize);
    long long int it = 0;
    while (performance(boardSize, reinas[0]) != 1) {
        // std::cout << avgPerf(reinas) << '\n';
        if (it % 1000 == 0) {
            for (coord &pos : reinas[0]) {
                std::cout << pos.x << " " << pos.y << "|";
            }
            std::cout << performance(boardSize, reinas[0]) << '\n';
        }
        reinas = derivePopulation(reinas);
        ++it;
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