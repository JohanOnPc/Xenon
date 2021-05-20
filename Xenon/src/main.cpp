#include "math/Vector.h"

#include <iostream>

int main() {
	xe::VectorF vec0(1, 0, 0);
	xe::VectorF vec1(0.05, 1, 0.02);
	xe::VectorF vec2(0.01, 0, 1);

	

	xe::Orthogonalize(vec0, vec1, vec2);

	std::cout << vec0 << ", " << vec1 << ", " << vec2 << "\n";
	std::cout << vec0.AngleBetween(vec1) * 180 / 3.1415 << ", " << vec0.AngleBetween(vec2) * 180 / 3.1415 << ", " << vec1.AngleBetween(vec2) * 180 / 3.1415 << "\n";
}