#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

const float mutationRate = 0.12;
const float popBest = 0.5;
const float popRandom = 0.2;

std::string original;

char random(char min = 'a', char max = 'z') {
    return min + (rand() % (max - min + 1));
}

struct individual {
    individual(std::string genes) {
        genome = genes;
        performance = perf(original);
    }
    individual(){};
    std::string genome;
    float performance;

    bool operator<(const individual &toComp) {
        return performance < toComp.performance;
    }
    bool operator>(const individual &toComp) {
        return performance > toComp.performance;
    }

    void mutate() {
        int position = random(0, genome.size() - 1);
        genome[position] = random();
        perf(original);
    }

    float perf(std::string orig) {
        float correct = 0;
        for (int i = 0; i < orig.size(); i++) {
            if (genome[i] == orig[i])
                correct++;
        }
        performance = correct / orig.size();
        return correct / orig.size();
    }
};

individual reproduce(individual parent, individual mother) {
    int position = random(0, parent.genome.size() - 1);
    individual child(
        parent.genome.substr(0, position) +
        mother.genome.substr(position, parent.genome.size() - position));
    return child;
}

individual generateIndividual(int size) {
    individual ind;
    for (int i = 0; i < size; i++) {
        ind.genome += random();
    }
    ind.perf(original);
    return ind;
}

std::vector<individual> generatePopulation(int genomeSize, int individuals) {
    std::vector<individual> population;
    for (int i = 0; i < individuals; i++) {
        population.push_back(generateIndividual(genomeSize));
        // std::cout << population.back().genome << '\n';
    }
    return population;
}

bool compare(const individual &a, const individual &b) {
    return a.performance > b.performance;
}

std::vector<individual> derivePopulation(std::vector<individual> population) {
    std::vector<individual> result;
    sort(begin(population), end(population), compare);
    std::vector<bool> selected(population.size(), false);
    for (int i = 0; i < population.size() * popBest; ++i) {
        result.push_back(population[i]);
        selected[i] = true;
    }
    for (int i = 0; i < population.size() * popRandom; ++i) {
        int pos = random(0, population.size() - 1);
        while (selected[pos]) {
            pos = random(0, population.size() - 1);
        }
        result.push_back(population[pos]);
        selected[pos] = true;
    }
    while (result.size() < population.size()) {
        individual child =
            reproduce(population[random(0, population.size() - 1)],
                      population[random(0, population.size() - 1)]);
        result.push_back(child);
    }
    // mutations
    for (int i = 0; i < result.size() - 1; i++) {
        if (random(1, 100) < ceil(mutationRate * 100)) {
            result[i].mutate();
        }
    }
    return result;
}

int main() {
    srand(time(NULL));
    std::cin >> original;
    long long int its = 0;
    double time = 0.0;
    for (int i = 0; i < 1; i++) {
        std::vector<individual> orig = generatePopulation(original.size(), 50);
        std::vector<individual> derived = derivePopulation(orig);
        auto start = std::chrono::system_clock::now();
        long long int it = 0;
        while (derived[0].performance < 1) {
            derived = derivePopulation(derived);
            if (it % 1000 == 0) {
                float perf = 0;
                for (const individual &el : derived) {
                    perf += el.performance;
                }
                std::cout << perf / derived.size() << std::endl;
            }
            ++it;
        }
        auto ends = std::chrono::system_clock::now();
        its += it;
        std::chrono::duration<double> diff = ends - start;
        time += diff.count();
    }
    std::cout << "prom it:" << its;
    std::cout << "prom time: " << time;

    return 0;
}