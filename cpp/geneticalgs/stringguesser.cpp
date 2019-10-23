#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

const float mutationRate = 0.01;
const float popBest = 0.5;
const float popRandom = 0.3;
const float popRem = 1 - (popBest + popRandom);

float performance(std::string original, std::string individual) {
    float correct = 0;
    for (int i = 0; i < original.size(); i++) {
        if (individual[i] == original[i])
            correct++;
    }
    return correct / original.size();
}

char random(char min = 'a', char max = 'z') {
    return min + (rand() % (max - min + 1));
}

std::string mutate(std::string individual) {
    int position = random(0, individual.size() - 1);
    individual[position] = random();
    return individual;
}

std::string reproduce(std::string parent, std::string mother) {
    int position = random(0, parent.size() - 1);
    std::string child = parent.substr(0, position) + mother.substr(position, parent.size() - position);
    return child;
}

std::string generateIndividual(int size) {
    std::string individual = "";
    for (int i = 0; i < size; i++) {
        individual += random();
    }
    return individual;
}

std::vector<std::string> generatePopulation(int genomeSize, int individuals) {
    std::vector<std::string> population;
    for (int i = 0; i < individuals; i++) {
        population.push_back(generateIndividual(genomeSize));
        std::cout << population.back() << '\n';
    }
    return population;
}

bool compare(const std::string &a, const std::string &b) {
    return a > b;
}

std::vector<std::string> derivePopulation (std::vector<std::string> population) {
    std::vector<std::string> result;
    sort(begin(population), end(population), compare);
    std::vector<bool> selected(population.size(), false);
    for (int i = 0; i < population.size() * popBest; ++i) {
        result.push_back(population[i]);
        selected[i] = true;
    }
    for (int i = 0; i < population.size() * popRandom; ++i) {
        pos = random(0, population.size() - 1);
        while (selected[pos]) {
`           pos = random(0, population.size() - 1);
        }
    }
    while (result < population.size()) {
        std::string child = merge(population[random(0, population.size() - 1)], population[random(0, population.size() - 1)]);
        result.push_back(child);
    }
    // mutations
    for (int i = 0; i < population.size() - 1; i++) {
        if (random(1, 100) == ceil(mutationRate * 100)) {
            populaltion[i] = mutate(population[i]);
        }
    }
    return result;
}

int main() {
    generatePopulation(10, 10);
    std::cout << reproduce("aabba", "ccdde");
    return 0;
}