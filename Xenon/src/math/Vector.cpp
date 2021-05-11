#include <math.h>

#include "Vector.h"
#include <cassert>

Vector3::Vector3(float x, float y, float z)
{
	_vec = _mm_set_ps(0.f, z, y, x);
}

Vector3::Vector3(__m128 _other) : _vec(_other) {}

Vector3 Vector3::operator+(const Vector3& other) const
{
	Vector3 vector = _mm_add_ps(_vec, other._vec);
	return vector;
}

Vector3 Vector3::operator+=(const Vector3& other)
{
	_vec = _mm_add_ps(_vec, other._vec);
	return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	Vector3 vector = _mm_sub_ps(_vec, other._vec);
	return vector;
}

Vector3 Vector3::operator-=(const Vector3& other)
{
	_vec = _mm_sub_ps(_vec, other._vec);
	return *this;
}

Vector3 Vector3::operator*(const int& scalar) const
{
	__m128 _scalar = _mm_set1_ps(scalar);
	Vector3 vector = _mm_mul_ps(_vec, _scalar);
	return vector;
}

Vector3 Vector3::operator*=(const int& scalar)
{
	__m128 _scalar =	_mm_set1_ps(scalar);
	_vec =				_mm_mul_ps(_vec, _scalar);
	return *this;
}

Vector3 Vector3::operator~()
{
	*this *= -1;
	return *this;
}

float Vector3::operator[](const int& index) const
{
	float vec[4];
	_mm_store_ps(vec, _vec);
	assert(index < 3);
	return vec[index];
}

float Vector3::Length() const
{
	__m128 _squared =	_mm_mul_ps(_vec, _vec);
	__m128 _sum =		_mm_hadd_ps(_squared, _squared);
	_sum =				_mm_hadd_ps(_sum, _sum);
	return				_mm_cvtss_f32(_mm_sqrt_ps(_sum));
}

void Vector3::Normalize()
{
	__m128 _squared =	_mm_mul_ps(_vec, _vec);
	__m128 _sum =		_mm_hadd_ps(_squared, _squared);
	_sum =				_mm_hadd_ps(_sum, _sum);
	__m128 _invRoot =	_mm_invsqrt_ps(_sum);
	_vec =				_mm_mul_ps(_vec, _invRoot);
}

float Vector3::DotProduct(const Vector3& other) const
{
	__m128 _mul =	_mm_mul_ps(_vec, other._vec);
	__m128 _sum =	_mm_hadd_ps(_mul, _mul);
	return			_mm_cvtss_f32(_mm_hadd_ps(_sum, _sum));
}

Vector3 Vector3::CrossProduct(const Vector3& other) const
{
	float x = (*this)[1] * other[2] - (*this)[2] * other[1];
	float y = (*this)[2] * other[0] - (*this)[0] * other[2];
	float z = (*this)[0] * other[1] - (*this)[1] * other[0];
	return Vector3(x, y, z);
}

float Vector3::AngleBetween(const Vector3& other) const
{
	float theta = this->DotProduct(other) / (this->Length() * other.Length());
	return acosf(theta);
}

Vector3 Vector3::OrtogonalProjection(const Vector3& other) const
{
	return other * (this->DotProduct(other) / (other.Length() * other.Length()));
}

std::ostream& operator<<(std::ostream& os, const Vector3 other)
{
	float vec[4];
	_mm_store_ps(vec, other._vec);
	os << "[" << vec[0] << ", " << vec[1] << ", " << vec[2] << "]";
	return os;
}
