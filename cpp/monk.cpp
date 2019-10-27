#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int sumOfDigits(int n) {
    int suma = 0;
    while (n > 0) {
        suma += n % 10;
        n /= 10;
    }
    return suma;
};

int Digit(int n) {
    if (n < 10)
        return n;
    else
        return Digit(sumOfDigits(n));
};

int maxSum(vector<int> arrdigit, int k) {
    int max = 0;
    for (int i = 0; i < k; i++) {
        int j = arrdigit.size() - 1 - i;
        max += arrdigit[j];
    }
    return max;
}

int minSum(vector<int> arrdigit, int k) {
    int min = 0;
    for (int i = 0; i < k; i++) {
        min += arrdigit[i];
    }
    return min;
}

int main() {
    vector<int> arr;
    vector<int> arrdigit;
    vector<pair<int, int>> query;

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        arr.push_back(temp);
        arrdigit.push_back(Digit(temp));
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        query.push_back(make_pair(a, b));
    }

    sort(arrdigit.begin(), arrdigit.end());

    for (int i = 0; i < q; i++) {
        // FUNCION QUE RECIBE TYPE Y K;
        if (query[i].first == 1)
            cout << maxSum(arrdigit, query[i].second);
        else
            cout << minSum(arrdigit, query[i].second);

        cout << endl;
    }
    return 0;
}
