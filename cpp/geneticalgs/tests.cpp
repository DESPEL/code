#include <iostream>
#include <vector>


int main () {
    std::vector<int> a = {1,2,3,4,5,6,7};
    std::vector<int> b = {2,3,4,5,6,7,8};
    std::vector<int> c;
    c.insert(c.begin(), a.begin() , a.begin() + 3);
    c.insert(c.begin(), b.begin() + 3 , b.end());
    std::cout << a.size() << " " << b.size() << " " << c.size();
}