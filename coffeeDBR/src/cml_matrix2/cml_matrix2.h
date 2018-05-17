#ifndef _CML_MATRIX2_H_
#define _CML_MATRIX2_H_
#include "../cml_vector/cml_Vector.h"

namespace cml
{
	class Matrix2
	{
	public:
		Matrix2();
		Matrix2(complex a11, complex a12, complex a21, complex a22);
		Matrix2(const Matrix2& mat);
		~Matrix2();
		static Matrix2 Identity();
		ComplexVector operator*(const ComplexVector&);
		Matrix2 operator*=(const Matrix2&);
		complex& operator[](const size_t);
		const complex& operator[](size_t) const;
	private:
		complex m_elements[4];
	};
}
cml::Matrix2 operator*(const cml::Matrix2& a, const cml::Matrix2& b);
cml::Matrix2 operator*(const long double& a, const cml::Matrix2& b);
#endif