// https://www.hackerrank.com/challenges/magic-square-forming
#include <cmath>
#include <iostream>

using namespace std;

int main() {
    int sq[8][9]{
        {8, 1, 6, 3, 5, 7, 4, 9, 2}, {6, 1, 8, 7, 5, 3, 2, 9, 4},
        {4, 9, 2, 3, 5, 7, 8, 1, 6}, {2, 9, 4, 7, 5, 3, 6, 1, 8},
        {8, 3, 4, 1, 5, 9, 6, 7, 2}, {4, 3, 8, 9, 5, 1, 2, 7, 6},
        {6, 7, 2, 1, 5, 9, 8, 3, 4}, {2, 7, 6, 9, 5, 1, 4, 3, 8},
    };
    int casillas[9];
    for (int &c : casillas) cin >> c;
    int min = 0, ac = 0;
    for (int *sqr : sq) {
        ac = 0;
        for (int i = 0; i < 9; ++i) ac += abs(sqr[i] - casillas[i]);
        if (ac < min)
            min = ac;
    }
    cout << min << '\n';
    return 0;
}