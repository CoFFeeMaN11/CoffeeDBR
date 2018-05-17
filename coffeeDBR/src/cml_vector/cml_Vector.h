#ifndef _CML_VECTOR_H_
#define _CML_VECTOR_H_
#include <stdlib.h>
#include <complex>

namespace cml
{
	typedef std::complex<long double> complex;
	class ComplexVector;
	class Vector
	{
	public:
		Vector();
		Vector(const size_t vectorSize);
		Vector(const Vector& vec);
		static Vector Unit(const size_t vectorSize, size_t pos);
		~Vector();
		void Init(size_t size);
		long double& operator[](size_t index);
		const long double& operator[](size_t index) const;
		Vector operator*(const long double& a) const;
		Vector operator+(const Vector& b) const;
		Vector operator-(const Vector& b) const;
		Vector operator=(const Vector& b);
		void Insert(long double* tab, size_t start, size_t size);
		static long double Dot(const Vector& a, const Vector& b);
		size_t getSize() const { return m_vectorSize; }
		long double Norm();
		operator ComplexVector();
	private:
		long double *m_elements;
		size_t m_vectorSize;
	};
	class ComplexVector
	{
	public:
		ComplexVector();
		ComplexVector(const size_t vectorSize);
		ComplexVector(const ComplexVector& vec);
		~ComplexVector();
		void Init(size_t size);
		
		complex& operator[](size_t index);
		const complex& operator[](size_t index) const;
		//Vector operator+(const Vector& b) const;
		//Vector operator-(const Vector& b) const;
		//Vector operator=(const Vector& b);
		//void Insert(complex* tab, size_t start, size_t size);
		size_t getSize() const { return m_vectorSize; }
	private:
		complex *m_elements;
		size_t m_vectorSize;
	};
}
cml::Vector operator*(const long double& a, const cml::Vector& b);
#endif