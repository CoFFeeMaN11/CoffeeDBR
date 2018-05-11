#ifndef _CML_MATRIX2_H_
#define _CML_MATRIX2_H_
#include "../cml_vector/cml_Vector.h"
#include <complex>
namespace cml
{
	template <typename T>
	class Matrix2
	{
	public:
		Matrix2<T>(T a11, T a12, T a21, T a22)
		{
			this->m_elements[0] = a11;
			this->m_elements[1] = a12;
			this->m_elements[2] = a21;
			this->m_elements[3] = a22;
		}
		Matrix2<T>(const Matrix2<T>& mat)
		{
			memcpy(m_elements, mat.m_elements, sizeof(T) * 4);
		}
		~Matrix2() {}
		static Matrix2<T> Identity()
		{
			return Matrix2<T>(T(1), T(0), T(0), T(1));
		}
		Vector operator*(const Vector<T,2>& vec)
		{
			assert(vec.getSize() == 2);
			cml::Vector<T, 2> temp(2);
			Matrix2<T> a(*this);
			temp[0] = a[0] * vec[0] + a[1] * vec[1];
			temp[1] = a[2] * vec[0] + a[3] * vec[1];
			return temp;
		}
		template<typename U> Matrix2<T> operator*(const Matrix2<U>& b)
		{
			cml::Matrix2 a(*this);
			T a11 = a[0] * T(b[0]) + a[1] * T(b[2]);
			T a12 = a[0] * T(b[1]) + a[1] * T(b[3]);
			T a21 = a[2] * T(b[0]) + a[3] * T(b[2]);
			T a22 = a[2] * T(b[1]) + a[3] * T(b[3]);
			return Matrix2<T>(a11, a12, a21, a22);
		}
		T& operator[](const size_t index)
		{
			assert(index < 4);
			return this->m_elements[index];
		}
		const T& operator[](size_t index) const
		{
			assert(index < 4);
			return this->m_elements[index];
		}
	private:
		T m_elements[4];
	};
}
#endif