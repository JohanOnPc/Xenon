#include <immintrin.h>
#include <iostream>


namespace xe {
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

		VectorF _vectorcall operator+(const VectorF& other) const;
		VectorF _vectorcall operator+=(const VectorF& other);
		VectorF _vectorcall operator-(const VectorF& other) const;
		VectorF _vectorcall operator-=(const VectorF& other);
		VectorF operator*(float scalar) const;
		VectorF operator*=(float scalar);
		VectorF operator~();
		float operator[](int index) const;

		float Length() const;
		void Normalize();
		void _vectorcall Rate(const VectorF& other, float dt);
		float _vectorcall DotProduct(const VectorF& other) const;
		VectorF _vectorcall CrossProduct(const VectorF& other) const;
		VectorF CrossProduct2() const;
		float _vectorcall AngleBetween(const VectorF& other) const;
		VectorF _vectorcall OrthogonalProjection(const VectorF& other) const;

		friend std::ostream& operator<<(std::ostream& os, const VectorF& other);
	};

	struct VectorD {
		__m256d _vec;

		VectorD(double x, double y);
		VectorD(double x, double y, double z);
		VectorD(double x, double y, double z, double w);
		VectorD(__m256d _other);

		VectorD _vectorcall operator+(const VectorD& other) const;
		VectorD _vectorcall operator+=(const VectorD& other);
		VectorD _vectorcall operator-(const VectorD& other) const;
		VectorD _vectorcall operator-=(const VectorD& other);
		VectorD operator*(double scalar) const;
		VectorD operator*=(double scalar);
		VectorD operator~();
		double operator[](int index) const;

		double Length() const;
		void Normalize();
		void _vectorcall Rate(const VectorD& other, double dt);
		double _vectorcall DotProduct(const VectorD& other) const;
		VectorD _vectorcall CrossProduct(const VectorD& other) const;
		VectorD CrossProduct2() const;
		double _vectorcall AngleBetween(const VectorD& other) const;
		VectorD _vectorcall OrthogonalProjection(const VectorD& other) const;

		friend std::ostream& operator<<(std::ostream& os, const VectorD& other);
	};

	void Orthogonalize(VectorF& v0, VectorF& v1, VectorF& v2);
	void Orthogonalize(VectorD& v0, VectorD& v1, VectorD& v2);
}

