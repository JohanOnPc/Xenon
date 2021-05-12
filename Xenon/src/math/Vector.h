#include <immintrin.h>
#include <iostream>

struct Vector {
	__m128 _vec;

	Vector(float x, float y);
	Vector(float x, float y, float z);
	Vector(float x, float y, float z, float w);
	Vector(__m128 _other);

	Vector operator+(const Vector& other) const;
	Vector operator+=(const Vector& other);
	Vector operator-(const Vector& other) const;
	Vector operator-=(const Vector& other);
	Vector operator*(float scalar) const;
	Vector operator*=(float scalar);
	Vector operator~();
	float operator[](int index) const;

	float Length() const;
	void Normalize();
	void Rate(const Vector& other, const float dt);
	float DotProduct(const Vector& other) const;
	Vector CrossProduct(const Vector& other) const;
	Vector CrossProduct2() const;
	float AngleBetween(const Vector& other) const;
	Vector OrthogonalProjection(const Vector& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Vector other);
};

