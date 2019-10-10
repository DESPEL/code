#include <iostream>

using namespace std;

float scanFloat(string msg = "") {
    float a;
    cout << msg << endl;
    cin >> a;
    return a;
}

int main() {
    cout << scanFloat("ingrese un numero") + scanFloat("ingrese otro numero");
}