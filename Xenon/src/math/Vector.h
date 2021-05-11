#include <immintrin.h>
#include <iostream>

struct Vector3 {
	__m128 _vec;

	Vector3(float x, float y, float z);
	Vector3(__m128 _other);

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator+=(const Vector3& other);
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator-=(const Vector3& other);
	Vector3 operator*(const int& scalar) const;
	Vector3 operator*=(const int& scalar);
	Vector3 operator~();
	float operator[](const int& index) const;

	float Length() const;
	void Normalize();
	float DotProduct(const Vector3& other) const;
	Vector3 CrossProduct(const Vector3& other) const;
	float AngleBetween(const Vector3& other) const;
	Vector3 OrtogonalProjection(const Vector3& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Vector3 other);
};

