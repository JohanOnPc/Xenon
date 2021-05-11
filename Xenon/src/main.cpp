#include "math/Vector.h"

#include <iostream>

int main() {
	Vector3 vec(1, 2, 3);

	std::cout << Vector3(1, 0, 0).CrossProduct(Vector3(0, 0, -1)) << "\n";
}