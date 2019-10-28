#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

struct edge {
    edge() {}
    edge(int t, int w) {
        weight = w;
        to = t;
    }
    int weight;
    int to;
};

struct AdjacencyList {
    unordered_map<int, vector<edge>> nodes;
    int size = 0;
    AdjacencyList() {}
    
    void insert(int idx, int to, int w = 0) {
        nodes[idx].emplace_back(to, w);
        size++;
    }
};

void dfs(AdjacencyList &graph, int index) {
    unordered_map<int, bool> visited;
    stack<int> visiting;
    visited[index] = true;
    visiting.push(index);
    while(!visiting.empty()) {
        int actual = visiting.top();
        visiting.pop();
        for (int i = 0; i < graph.nodes[actual].size(); i++) {
            if (!visited[graph.nodes[actual][i].to]) {
                visiting.push(graph.nodes[actual][i].to);
                visited[graph.nodes[actual][i].to] = true;
            }
        }
    }
}

int main () {
    AdjacencyList a;
    a.insert(1,2,1);
    a.insert(3,1,1);
    a.insert(2,1,1);
    a.insert(4,2,1);
    a.insert(1,3,1);
    a.insert(1,5,1);
    a.insert(5,1,1);
    a.insert(3,2,1);
    a.insert(5,6,1);
    dfs(a, 4);
}