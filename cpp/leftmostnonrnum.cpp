// https://www.codewars.com/kata/59113da398dcd456270000a8
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (string num : nums) {
        unordered_map<char, int> letras;
        for (char c : num) {
            letras[c]++;
        }
        bool corr = true;
        for (unordered_map<char, int>::iterator it = letras.begin();
             it != letras.end(); it++) {
            if (it->second > 1) {
                corr = false;
            }
        }
        if (corr) {
            cout << num;
            return 0;
        }
    }
    cout << "-1";
}