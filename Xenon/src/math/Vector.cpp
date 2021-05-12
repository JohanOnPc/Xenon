#include <math.h>

#include "Vector.h"
#include <cassert>

Vector::Vector(float x, float y)
{
	_vec = _mm_set_ps(0.f, 0.f, y, x);
}

Vector::Vector(float x, float y, float z)
{
	_vec = _mm_set_ps(0.f, z, y, x);
}

Vector::Vector(float x, float y, float z, float w)
{
	_vec = _mm_set_ps(w, z, y, x);
}

Vector::Vector(__m128 _other) : _vec(_other) {}

Vector Vector::operator+(const Vector& other) const
{
	Vector vector = _mm_add_ps(_vec, other._vec);
	return vector;
}

Vector Vector::operator+=(const Vector& other)
{
	_vec = _mm_add_ps(_vec, other._vec);
	return *this;
}

Vector Vector::operator-(const Vector& other) const
{
	Vector vector = _mm_sub_ps(_vec, other._vec);
	return vector;
}

Vector Vector::operator-=(const Vector& other)
{
	_vec = _mm_sub_ps(_vec, other._vec);
	return *this;
}

Vector Vector::operator*(const float scalar) const
{
	__m128 _scalar = _mm_set1_ps(scalar);
	Vector vector = _mm_mul_ps(_vec, _scalar);
	return vector;
}

Vector Vector::operator*=(const float scalar)
{
	__m128 _scalar = _mm_set1_ps(scalar);
	_vec = _mm_mul_ps(_vec, _scalar);
	return *this;
}

Vector Vector::operator~()
{
	*this *= -1;
	return *this;
}

float Vector::operator[](const int index) const
{
	float vec[4];
	_mm_store_ps(vec, _vec);
	assert(index < 4);
	return vec[index];
}

float Vector::Length() const
{
	__m128 _squared = _mm_mul_ps(_vec, _vec);
	__m128 _sum = _mm_hadd_ps(_squared, _squared);
	_sum = _mm_hadd_ps(_sum, _sum);
	return _mm_cvtss_f32(_mm_sqrt_ps(_sum));
}

void Vector::Normalize()
{
	__m128 _squared = _mm_mul_ps(_vec, _vec);
	__m128 _sum = _mm_hadd_ps(_squared, _squared);
	_sum = _mm_hadd_ps(_sum, _sum);
	__m128 _invRoot = _mm_invsqrt_ps(_sum);
	_vec = _mm_mul_ps(_vec, _invRoot);
}

void Vector::Rate(const Vector& other, const float dt)
{
	__m128 _rate = _mm_set_ps1(dt);
	_vec = _mm_fmadd_ps(other._vec, _rate, _vec);
}

float Vector::DotProduct(const Vector& other) const
{
	__m128 _mul = _mm_mul_ps(_vec, other._vec);
	__m128 _sum = _mm_hadd_ps(_mul, _mul);
	return _mm_cvtss_f32(_mm_hadd_ps(_sum, _sum));
}

Vector Vector::CrossProduct(const Vector& other) const
{
	float x = (*this)[1] * other[2] - (*this)[2] * other[1];
	float y = (*this)[2] * other[0] - (*this)[0] * other[2];
	float z = (*this)[0] * other[1] - (*this)[1] * other[0];
	return Vector(x, y, z);
}

Vector Vector::CrossProduct2() const
{
	float x = -(*this)[1];
	float y = (*this)[0];
	return Vector(x, y);
}

float Vector::AngleBetween(const Vector& other) const
{
	float theta = this->DotProduct(other) / (this->Length() * other.Length());
	return acosf(theta);
}

Vector Vector::OrthogonalProjection(const Vector& other) const
{
	return other * (this->DotProduct(other) / (other.Length() * other.Length()));
}

std::ostream& operator<<(std::ostream& os, const Vector other)
{
	float vec[4];
	_mm_store_ps(vec, other._vec);
	os << "[" << vec[0] << ", " << vec[1] << ", " << vec[2] << ", " << vec[3] << "]";
	return os;
}
