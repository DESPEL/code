#include <iostream>
#include <corecrt_math_defines.h>

void E1() {
	int a = 5;
	std::cout << a << '\n';
	std::cout << &a << '\n';
	int* pa = &a;
	std::cout << pa << '\n';
	std::cout << *pa << '\n';
}

void E2() {
	for (const int& ph : {2,4,6,8,10})
		std::cout << "d: " << &ph << " v: " << ph << '\n';
}

float* E3(float r) {
	float* c = new float[3];
	c[0] = r * r * (float)M_PI, c[1] = 2 * r * (float)M_PI, c[2] = 2 * r;
	return c;
}
int main() {
	std::cout << '\n' << "Ejercicio 1:" << '\n';
	E1();
	std::cout << '\n' << "Ejercicio 2:" << '\n';
	E2();
	std::cout << '\n' << "Ejercicio 3:" << '\n';
	float* c = E3(5);
	for (int i = 0; i < 3; i++)
		std::cout << c[i] << '\n';
}