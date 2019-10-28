//https://www.hackerrank.com/challenges/even-tree/problem
#include <iostream>
#include <unordered_map>

using namespace std;

struct tree {
    unordered_map<int, vector<int>> nodes;

    void insert(int idx, int to) {
        nodes[idx].push_back(to);
    }
};

pair<int,int> eventree(tree &graph, int idx = 1) {
    int total = 0, nsub = 1;
    for (int i = 0; i < graph.nodes[idx].size(); i++) {
        pair<int,int> tempres = eventree(graph, graph.nodes[idx][i]);
        total += tempres.first;
        nsub += tempres.second;
    }
    if (nsub % 2 == 0 && idx != 1) 
        total++;
    return make_pair(total, nsub);
}


int main () {
    int n, v, t1, t2;
    cin >> n >> v;
    tree a;
    for (int i = 0; i < v; i++) {
        cin >> t1 >> t2;
        a.nodes[t2].push_back(t1);
    }
    pair<int,int> res = eventree(a);
    cout << res.first << '\n';
    return 0;
}