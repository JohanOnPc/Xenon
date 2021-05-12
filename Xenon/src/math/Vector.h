#include <immintrin.h>
#include <iostream>


#ifndef VECTORSINGLE
using Vector = struct VectorD;
#else
using Vector = struct VectorF
#endif

struct VectorF {
	__m128 _vec;

	VectorF(float x, float y);
	VectorF(float x, float y, float z);
	VectorF(float x, float y, float z, float w);
	VectorF(__m128 _other);

	VectorF operator+(const VectorF& other) const;
	VectorF operator+=(const VectorF& other);
	VectorF operator-(const VectorF& other) const;
	VectorF operator-=(const VectorF& other);
	VectorF operator*(float scalar) const;
	VectorF operator*=(float scalar);
	VectorF operator~();
	float operator[](int index) const;

	float Length() const;
	void Normalize();
	void Rate(const VectorF& other, float dt);
	float DotProduct(const VectorF& other) const;
	VectorF CrossProduct(const VectorF& other) const;
	VectorF CrossProduct2() const;
	float AngleBetween(const VectorF& other) const;
	VectorF OrthogonalProjection(const VectorF& other) const;

	friend std::ostream& operator<<(std::ostream& os, const VectorF& other);
};

struct VectorD {
	__m256d _vec;

	VectorD(double x, double y);
	VectorD(double x, double y, double z);
	VectorD(double x, double y, double z, double w);
	VectorD(__m256d _other);

	VectorD operator+(const VectorD& other) const;
	VectorD operator+=(const VectorD& other);
	VectorD operator-(const VectorD& other) const;
	VectorD operator-=(const VectorD& other);
	VectorD operator*(double scalar) const;
	VectorD operator*=(double scalar);
	VectorD operator~();
	double operator[](int index) const;

	double Length() const;
	void Normalize();
	void Rate(const VectorD& other, double dt);
	double DotProduct(const VectorD& other) const;
	VectorD CrossProduct(const VectorD& other) const;
	VectorD CrossProduct2() const;
	double AngleBetween(const VectorD& other) const;
	VectorD OrthogonalProjection(const VectorD& other) const;

	friend std::ostream& operator<<(std::ostream& os, const VectorD& other);
};

