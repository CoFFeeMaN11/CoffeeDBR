#ifndef _CML_MATRIX2_H_
#define _CML_MATRIX2_H_
#include "../cml_vector/cml_Vector.h"

namespace cml
{
	class Matrix2
	{
	public:
		Matrix2(long double a11,long double a12,long double a21,long double a22);
		Matrix2(const Matrix2& mat);
		~Matrix2();
		static Matrix2 Identity();
		Vector operator*(const Vector&);
		Matrix2 operator*(const Matrix2&);
		long double& operator[](const size_t);
		const long double& operator[](size_t) const;
	private:
		long double m_elements[4];
	};
}
#endif