// https://www.hackerrank.com/challenges/construct-the-array/problem
#include <iostream>
#define M 1000000007

using namespace std;

long long int mulmod(long long int a, long long int b, long long int mod = M) {
    long long int res = 0;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1)
            res = (res + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return res % mod;
}

int nways (int n, int k, int x) {
    long long int ways[n][2];
    ways[0][0] = 1;
    ways[1][0] = 0;
    ways[0][1] = 0;
    ways[1][1] = 1;

    for (int i = 2; i < n; i++) {
        ways[0][i] = mulmod(ways[1][i - 1], k - 1);
        ways[1][i] = (mulmod(ways[1][i - 1], k - 2) + ways[0][i - 1] % M) % M;
    }

    if (x == 1)
        return ways[0][n - 1];
    return ways[1][n - 1];
}


int main() {
    int n,k,x;
    cin >> n >> k >> x;
    cout << nways(n,k,x);
}
