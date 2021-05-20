#include <math.h>
#include <cassert>

#include "Vector.h"

namespace xe {

	VectorF::VectorF(float x, float y) : _vec(_mm_set_ps(0.f, 0.f, y, x)) {}

	VectorF::VectorF(float x, float y, float z) : _vec(_mm_set_ps(0.f, z, y, x)) {}

	VectorF::VectorF(float x, float y, float z, float w) : _vec(_mm_set_ps(w, z, y, x)) {}

	VectorF::VectorF(const __m128 _other) : _vec(_other) {}

	VectorF VectorF::operator+(const VectorF& other) const
	{
		VectorF VectorF = _mm_add_ps(_vec, other._vec);
		return VectorF;
	}

	VectorF VectorF::operator+=(const VectorF& other)
	{
		_vec = _mm_add_ps(_vec, other._vec);
		return *this;
	}

	VectorF VectorF::operator-(const VectorF& other) const
	{
		VectorF VectorF = _mm_sub_ps(_vec, other._vec);
		return VectorF;
	}

	VectorF VectorF::operator-=(const VectorF& other)
	{
		_vec = _mm_sub_ps(_vec, other._vec);
		return *this;
	}

	VectorF VectorF::operator*(const float scalar) const
	{
		__m128 _scalar = _mm_set1_ps(scalar);
		VectorF VectorF = _mm_mul_ps(_vec, _scalar);
		return VectorF;
	}

	VectorF VectorF::operator*=(const float scalar)
	{
		__m128 _scalar = _mm_set1_ps(scalar);
		_vec = _mm_mul_ps(_vec, _scalar);
		return *this;
	}

	VectorF VectorF::operator~()
	{
		*this *= -1;
		return *this;
	}

	float VectorF::operator[](const int index) const
	{
		float vec[4];
		_mm_store_ps(vec, _vec);
		assert(index < 4);
		return vec[index];
	}

	float VectorF::Length() const
	{
		__m128 _sum = _mm_dp_ps(_vec, _vec, 0xff);
		return _mm_cvtss_f32(_mm_sqrt_ps(_sum));
	}

	void VectorF::Normalize()
	{
		__m128 _sum = _mm_dp_ps(_vec, _vec, 0xff);
		__m128 _invRoot = _mm_invsqrt_ps(_sum);
		_vec = _mm_mul_ps(_vec, _invRoot);
	}

	void VectorF::Rate(const VectorF& other, const float dt)
	{
		__m128 _rate = _mm_set_ps1(dt);
		_vec = _mm_fmadd_ps(other._vec, _rate, _vec);
	}

	float VectorF::DotProduct(const VectorF& other) const
	{
		return _mm_cvtss_f32(_mm_dp_ps(_vec, other._vec, 0xff));
	}

	VectorF VectorF::CrossProduct(const VectorF& other) const
	{
		float x = (*this)[1] * other[2] - (*this)[2] * other[1];
		float y = (*this)[2] * other[0] - (*this)[0] * other[2];
		float z = (*this)[0] * other[1] - (*this)[1] * other[0];
		return VectorF(x, y, z);
	}

	VectorF VectorF::CrossProduct2() const
	{
		float x = -(*this)[1];
		float y = (*this)[0];
		return VectorF(x, y);
	}

	float VectorF::AngleBetween(const VectorF& other) const
	{
		float theta = this->DotProduct(other) / (this->Length() * other.Length());
		return acosf(theta);
	}

	VectorF VectorF::OrthogonalProjection(const VectorF& other) const
	{
		return *this * (this->DotProduct(other) / DotProduct(*this));
	}

	std::ostream& operator<<(std::ostream& os, const VectorF& other)
	{
		float vec[4];
		_mm_store_ps(vec, other._vec);
		os << "[" << vec[0] << ", " << vec[1] << ", " << vec[2] << ", " << vec[3] << "]";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const VectorD& other)
	{
		double vec[4];
		_mm256_store_pd(vec, other._vec);
		os << "[" << vec[0] << ", " << vec[1] << ", " << vec[2] << ", " << vec[3] << "]";
		return os;
	}

	VectorD::VectorD(double x, double y) : _vec(_mm256_set_pd(0., 0., y, x)) {}

	VectorD::VectorD(double x, double y, double z) : _vec(_mm256_set_pd(0., z, y, x)) {}

	VectorD::VectorD(double x, double y, double z, double w) : _vec(_mm256_set_pd(w, z, y, x)) {}

	VectorD::VectorD(const __m256d _other) : _vec(_other) {}

	VectorD VectorD::operator+(const VectorD& other) const
	{
		return VectorD(_mm256_add_pd(_vec, other._vec));
	}

	VectorD VectorD::operator+=(const VectorD& other)
	{
		_vec = _mm256_add_pd(_vec, other._vec);
		return *this;
	}

	VectorD VectorD::operator-(const VectorD& other) const
	{
		return VectorD(_mm256_sub_pd(_vec, other._vec));
	}

	VectorD VectorD::operator-=(const VectorD& other)
	{
		_vec = _mm256_sub_pd(_vec, other._vec);
		return *this;
	}

	VectorD VectorD::operator*(const double scalar) const
	{
		__m256d _scalar = _mm256_set1_pd(scalar);
		return VectorD(_mm256_mul_pd(_vec, _scalar));
	}

	VectorD VectorD::operator*=(const double scalar)
	{
		__m256d _scalar = _mm256_set1_pd(scalar);
		_vec = _mm256_mul_pd(_vec, _scalar);
		return *this;
	}

	VectorD VectorD::operator~()
	{
		*this *= -1;
		return *this;
	}

	double VectorD::operator[](const int index) const
	{
		double vec[4];
		_mm256_store_pd(vec, _vec);
		assert(index < 4);
		return vec[index];
	}

	double VectorD::Length() const
	{
		__m256d _squared = _mm256_mul_pd(_vec, _vec);
		__m128d _high = _mm256_extractf128_pd(_squared, 1);
		__m128d _low = _mm256_castpd256_pd128(_squared);
		_low = _mm_add_pd(_low, _high);
		_high = _mm_unpackhi_pd(_low, _low);
		__m128d _sum = _mm_add_pd(_low, _high);
		return _mm_cvtsd_f64(_mm_sqrt_pd(_sum));
	}

	void VectorD::Normalize()
	{
		__m256d _squared = _mm256_mul_pd(_vec, _vec);
		__m256d _sum = _mm256_hadd_pd(_squared, _squared);
		_sum = _mm256_hadd_pd(_sum, _sum);
		__m256d _invRoot = _mm256_invsqrt_pd(_sum);
		_vec = _mm256_mul_pd(_vec, _invRoot);
	}

	void VectorD::Rate(const VectorD& other, double dt)
	{
		__m256d _rate = _mm256_set1_pd(dt);
		_vec = _mm256_fmadd_pd(other._vec, _rate, _vec);
	}

	double VectorD::DotProduct(const VectorD& other) const
	{
		__m256d _mul = _mm256_mul_pd(_vec, other._vec);
		__m256d _sum = _mm256_hadd_pd(_mul, _mul);
		return _mm256_cvtsd_f64(_mm256_hadd_pd(_sum, _sum));
	}

	VectorD VectorD::CrossProduct(const VectorD& other) const
	{
		double x = (*this)[1] * other[2] - (*this)[2] * other[1];
		double y = (*this)[2] * other[0] - (*this)[0] * other[2];
		double z = (*this)[0] * other[1] - (*this)[1] * other[0];
		return VectorD(x, y, z);
	}

	VectorD VectorD::CrossProduct2() const
	{
		double x = -(*this)[1];
		double y = (*this)[0];
		return VectorD(x, y);
	}

	double VectorD::AngleBetween(const VectorD& other) const
	{
		double theta = this->DotProduct(other) / (this->Length() * other.Length());
		return acos(theta);
	}

	VectorD VectorD::OrthogonalProjection(const VectorD& other) const
	{
		return *this * (this->DotProduct(other) / DotProduct(*this));
	}

	void Orthogonalize(VectorF& v0, VectorF& v1, VectorF& v2)
	{
		///v0.Normalize();
		//v2 = v0.CrossProduct(v1);
		//v2.Normalize();
		//v1 = v2.CrossProduct(v2);

		v1 -= (v0.OrthogonalProjection(v1));
		v2 -= (v0.OrthogonalProjection(v2) + v1.OrthogonalProjection(v2));

		v0.Normalize();
		v1.Normalize();
		v2.Normalize();
	}

	void Orthogonalize(VectorD& v0, VectorD& v1, VectorD& v2)
	{
		v0.Normalize();
		v2 = v0.CrossProduct(v1);
		v2.Normalize();
		v1 = v2.CrossProduct(v2);
	}
}


