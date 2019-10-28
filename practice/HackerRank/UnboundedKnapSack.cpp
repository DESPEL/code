// https://www.hackerrank.com/challenges/unbounded-knapsack/problem?h_r=internal-search
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int maxsum(vector<int> &items, unordered_map<string, int> &mem, int sum,
           int idx) {
    if (idx < 0)
        return sum;
    if (sum == 0) {
        return 0;
    }
    string key = to_string(sum);
    if (mem.find(key) != end(mem))
        return mem[key];
    int tempr;
    if (sum - items[idx] >= 0)
        tempr = min(maxsum(items, mem, sum - items[idx], idx - 1),
                    min(maxsum(items, mem, sum, idx - 1),
                    maxsum(items, mem, sum - items[idx], idx)));
    else 
        tempr = maxsum(items, mem, sum, idx - 1);
    return tempr;
}

int knapsack(vector<int> &items, int obj) { 
    unordered_map<string, int> mem; 
    sort(begin(items), end(items));
    return obj - maxsum(items, mem, obj, items.size() - 1);
}

int main() {
    int n;
    cin >> n;
    for (int z = 0; z < n; z++) {
        int n, val, temp;
        cin >> n >> val;
        vector<int> vals;
        for (int i = 0; i < n; i++) {
            cin >> temp;
            vals.push_back(temp);
        }
        cout << knapsack(vals, val) << '\n';
    }
}