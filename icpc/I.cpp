#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int main () {
    map <int,int> a;
    a[1] = 1;
    a[4] = 4;
    a[5] = 5;
    a[2] = 2;
    a[3] = 3;
   
    for (pair<const int,int> &v: a) {
        std::cout << v.first << ' ';
    }
}