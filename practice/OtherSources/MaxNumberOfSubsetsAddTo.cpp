// https://www.youtube.com/watch?feature=youtu.be&v=nqlNzOcnCfs&app=desktop
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int nsubarr(const vector<int> &arr, unordered_map<string, int> &mem, int sum,
            int idx) {
    if (sum == 0)
        return 1;
    if (sum < 0)
        return 0;
    if (idx < 0)
        return 0;
    string key = to_string(idx) + ":" + to_string(sum);
    if (mem.find(key) != end(mem))
        return mem[key];
    int tempr;
    if (arr[idx] <= sum)
        tempr = nsubarr(arr, mem, sum - arr[idx], idx - 1) +
                nsubarr(arr, mem, sum, idx - 1);
    else
        tempr = nsubarr(arr, mem, sum, idx - 1);
    mem[key] = tempr;
    return tempr;
}

int maxsubarr(const vector<int> &arr, int sum) {
    unordered_map<string, int> mem;
    return nsubarr(arr, mem, sum, arr.size() - 1);
}

int main() {
    int sum = 16;
    vector<int> v = {2, 4, 6, 10};
    cout << maxsubarr(v, sum);
}