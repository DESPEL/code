#include <iostream>
#include <vector>
#include <queue>
#include <map>

struct node {
    std::vector<int> adj;
    int minp;
};

struct element {
    int pasos;
    int idx;

    bool operator<(const element &b) const {return pasos < b.pasos;}
};


std::vector<node> toGraph(std::vector<int> &elements) {
    std::vector<node> graph(elements.size());
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i] > i) {
            graph[i].adj.push_back(i);
        } else {
            graph[i].adj.push_back(i + 1);
        }
    }
    return graph;
}

int pasos(std::vector<int> elements) {
    std::vector<int> minp(elements.size());
    std::priority_queue<element, std::vector<element>> cola;
    element actual;
    actual.pasos = 0;
    actual.idx = 0;
    minp[0] = 0;
    cola.emplace(actual);
    while (!cola.empty()) {
        
    }


}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> elementos(n);
    for (int i = 0; i < n; i++) {
        std::cin >> elementos[i];
    }
}
