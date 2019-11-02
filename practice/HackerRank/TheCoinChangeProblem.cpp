// https://www.hackerrank.com/challenges/coin-change/problem
#include <iostream>
#include <vector>


using namespace std;

long long int nways(const vector<int> &coins,int sum) {
    long long int dp[coins.size()+1][sum+1];
    for (int i = 0; i <= coins.size(); i++)
        dp[i][0] = 1;
    for (int i = 0; i <= sum; i++)
        dp[0][i] = 0;
    for (int i = 0; i < coins.size(); i++) {
        for (int j = 1; j <= sum; j++) {
            if(j - coins[i] < 0)
                dp[i+1][j] = dp[i][j];
            else
                dp[i+1][j] = dp[i + 1][j - coins[i]] + dp[i][j];
        }
    }
    /*
    cout << '\n';
    for (int i = 0; i <= coins.size(); i++) {
        for (int j = 0; j <= sum; j++) {
            cout << dp[i][j] << ' ';
        }
        cout << '\n';
    }*/
    return dp[coins.size()][sum];
}


int main () {
    int n, m;
    cin >> n >> m;
    vector<int> cvs(m);
    for (int i = 0; i < m; i++) {
        cin >> cvs[i];
    }
    cout << nways(cvs, n);
}

