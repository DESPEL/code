// https://www.hackerrank.com/challenges/the-quickest-way-up/problem
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct pos {
    pos(int t, int po) {
        tiros = t;
        p = po;
    }
    int tiros;
    int p;
};

int quickestWayUp(vector<vector<int>> ladders = {}, vector<vector<int>> snakes = {}) {
    auto comp2 = [](const pos &p1, const pos &p2) {
        if (p1.p == p2.p) {
            return p1.tiros < p2.tiros;
        } else {
            return p1.p < p2.p;
        }
    };
    priority_queue<pos, vector<pos>, decltype(comp2)> caminos(comp2);

    caminos.emplace(1, 2);
    caminos.emplace(1, 3);
    caminos.emplace(2, 1);
    cout << caminos.top().p;
}

int main() {
    quickestWayUp();
}