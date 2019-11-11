// https://www.hackerrank.com/challenges/linkedin-practice-dynamic-programming-lcs
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct res {
    int sz = 0;
    vector<int> vals;
};

bool operator < (const res &r1, const res &r2) {
    return r1.sz < r2.sz;
}

res lcs(vector<int> vs1, vector<int> vs2, unordered_map<string, res> &memo){
    if (vs1.empty() || vs2.empty())
        return res();
    string key = to_string(vs1.size()) + ":" + to_string(vs1[vs1.size() - 1]) + ":" + to_string(vs2.size()) + ":" + to_string(vs2[vs2.size() - 1]);
    if (memo.find(key) != end(memo))
        return memo[key];
    vector<int> a = vs1;
    vector<int> b = vs2;
    a.pop_back();
    b.pop_back();
    res maxval;
    res t1, t2, t3;
    if (vs1[vs1.size() - 1] == vs2[vs2.size() - 1]) {
        t1 = lcs(a, b, memo);
        t1.vals.push_back(vs1[vs1.size() - 1]);
        t1.sz++;
    }
    t2 = lcs(a, vs2, memo);
    t3 = lcs(vs1, b, memo);
    res vmax = max(t1, max(t2, t3));
    memo[key] = vmax;
    return vmax;
}

int main () {
    vector<int> a, b;
    int n1, n2;
    cin >> n1 >> n2;
    int c;
    unordered_map<string, res> memo;
    for (int i = 0 ; i < n1; i++) {
        cin >> c;
        a.push_back(c);
    }
    for (int i = 0; i < n2; i++) {
        cin >> c;
        b.push_back(c);
    }
    for (const int &c : lcs(a, b, memo).vals)
        cout << c << ' ';
}
