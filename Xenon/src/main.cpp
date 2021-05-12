#include "math/Vector.h"

#include <iostream>

int main() {
	VectorD vec(1, 0, 0);
	VectorD other(0, 0, 1);

	std::cout << vec.OrthogonalProjection(other) << "\n";
	std::cout << other << " -> " << other.Length() << " -> " << vec.DotProduct(other) << "\n";
}