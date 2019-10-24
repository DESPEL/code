#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

const float mutationRatio = 0.1;
const float preserveBest = 0.5;
const float preserveRandom = 0.2;
const int popSize = 20;

struct coord {
    coord(int px, int py) {x = px, y = py;}
    coord() {}
    int x,y;
}

int random(int min, int max) {
    return min + (rand() % (max - min + 1)); 
}

// gene, indivual, mutation, merge, performance, avgperf
// population, derive pop, loop solver

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

coord gene(int px, int ngenes) {
    return coord(px, random(0, ngenes - 1));
}

std::vector<coord> individual(int ngenes) {
    std::vector<coord> chromosome;
    for (int i = 0; i < ngenes; i++) {
        chromosome.append(gene(i, ngenes));
    }
    return chromosome;
}

std::vector<std::vector<coord>> population(int ngenes, int individuals) {
    std::vector<std::vector<coord>> chromosomes;
    for (int i = 0; i < individuals; i++) {
        chromosomes.push_back(individual(ngenes));
    }
    return chromosomes;
}

std::vector<coord> mutate(std::vector<coord> &chromosome) {
    std::vector<coord> result = chromosome;
    int index = random(0, chromosome.size() - 1);
    result[index] = gene(index, chromosome.size() - 1)
}