#include <iostream>
#include <corecrt_math_defines.h>


void E1() {
    int a = 5;
    std::cout << a << '\n';
    std::cout << &a << '\n';
    int *pa = &a;
    std::cout << pa << '\n';
    std::cout << *pa << '\n';
}

void E2() {
    int h[] = {2,4,6,8,10};
    int *ph = h;
    for (int i = 0; i < 5; i++) {
        std::cout << &ph[i] << " " << ph[i] << '\n';
    }
}

float* E3(float r) {
    float *c = new float[3];
    c[0] = r * r * (float)M_PI, c[1] = 2 * r * (float)M_PI, c[2] =  2 * r;
    return c;
}
int main () {
    E1();
    E2();
    float * c = E3(5);
    for (int i = 0; i < 3; i++)
        std::cout << c[i] << '\n';
}