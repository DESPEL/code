// https://www.hackerrank.com/challenges/picking-numbers/
#include <iostream>
#include <unordered_map>

using namespace std;

int main () {
    int n, val;
    cin >> n;
    unordered_map<int,int> vals;
    for (int i = 0; i < n; i++) {
        cin >> val;
        vals[val]++;
        vals[val+1]++;
    }
    int max = 0;
    for (pair<const int,int> &can : vals) 
        if (can.second > max) max = can.second;
    cout << max;
    return 0;
}