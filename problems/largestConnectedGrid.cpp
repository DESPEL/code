/// https://www.geeksforgeeks.org/largest-connected-component-on-a-grid/
#include <iostream>
#include <vector>
#include <queue>

struct coord {
    int r;
    int c;
    int val;
};

int offsetr[] = {1,0,-1,0};
int offsetc[] ={0,1,0,-1};

// Complexity O(n)
int nElements(std::vector<std::vector<int>> &mapa, std::vector<std::vector<bool>> &vis, int pr, int pc) {
    std::queue<coord> cola;
    coord actual;
    actual.r = pr;
    actual.c = pc;
    actual.val = mapa[pr][pc];
    coord temp;
    vis[pr][pc] = true;
    cola.emplace(actual);
    int el = 0;
    while (!cola.empty()) {
        el++;
        actual = cola.front();
        cola.pop();
        //std::cout << cola.size() << std::endl;
        for (int i = 0; i < 4; i++) {
            if (actual.r + offsetr[i] < 0 || actual.c + offsetc[i] < 0) continue;
            if (actual.r + offsetr[i] >= mapa.size() || actual.c + offsetc[i] >= mapa[0].size()) continue;
            if (!vis[actual.r + offsetr[i]][actual.c + offsetc[i]]) {
                if (mapa[actual.r + offsetr[i]][actual.c + offsetc[i]] == actual.val) {
                    temp.r = actual.r + offsetr[i];
                    temp.c = actual.c + offsetc[i];
                    temp.val = actual.val;
                    vis[temp.r][temp.c] = true;
                    cola.emplace(temp);
                }
            }
            //std::cout << "a" << std::endl;
        }
    }
    return el;
}

// Complexity worst case O(n^2) best case O(n)
int largestConnectedC(std::vector<std::vector<int>> &mapa, int r, int c) {
    int maxc = 0, actualc;
    std::vector<std::vector<bool>> vis(r, std::vector<bool>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (!vis[i][j]) {
                actualc = nElements(mapa, vis, i, j);
            }else continue;

            if (actualc > maxc) maxc = actualc;
        }
    }
    return maxc;
}

int main () {
    int r, c, tmp;
    std::cin >> r >> c;
    std::vector<std::vector<int>> mapa;

    for (int i = 0; i < r; i++) {
        mapa.push_back(std::vector<int>());
        for (int j = 0; j < c; j++) {
            std::cin >> tmp;
            mapa[i].push_back(tmp);
        }
    }

    std::cout << largestConnectedC(mapa, r, c) << std::endl;

}
