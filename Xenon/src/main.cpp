#include "math/Vector.h"

#include <iostream>

int main() {
	Vector vec(1, 2, 3);

	std::cout << Vector(1, 0, 0).CrossProduct(Vector(0, 0, -1)) << "\n";
	vec.Rate(Vector(1, 1, 11), 0.01);
	std::cout << vec << "\n";
	std::cout << Vector(2, 2).CrossProduct2() << "\n";
}