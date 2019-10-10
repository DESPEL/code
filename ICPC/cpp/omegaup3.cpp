#include <bits/stdc++.h>

using namespace std;

// Complete the hackerrankInString function below.
string hackerrankInString(string s) {
    string hackerrank = "hackerrank";
    int pos = 0;
    int fin = hackerrank.size() - 1;
    for (int i = 0; i < s.size(); i++) {
        if(hackerrank[pos] == s[i]) pos++;
        cout << pos << endl;
    }
    if (pos == fin) {
        return "YES";
    } else {
        return "NO";
    }

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        string result = hackerrankInString(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
