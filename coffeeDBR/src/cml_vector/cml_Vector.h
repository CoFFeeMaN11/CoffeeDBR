#ifndef _CML_VECTOR_H_
#define _CML_VECTOR_H_
#include <stdlib.h>
#include <cassert>
#include <Windows.h>
namespace cml
{
	template<typename T = long double, size_t _size = 2>class Vector
	{
	public:
		Vector<T, _size>() : m_vectorSize(_size)
		{
			m_elements = new T[_size];
			ZeroMemory(m_elements, sizeof(T)*_size);
		}
		Vector<T, _size>(const Vector<T, _size>& vec)
		{
			this->m_elements = new long double[vec.getSize()];
			for (int i = 0; i < vec.getSize(); i++)
				m_elements[i] = vec[i];
			m_vectorSize = vec.m_vectorSize;
		}
		T& operator[](size_t index)
		{
			assert(index < m_vectorSize);
			return m_elements[index];
		}
		const T& operator[](size_t index) const
		{
			assert(index < _size);
			return m_elements[index];
		}
		static Vector<T, _size> Unit(size_t pos)
		{
			Vector<T, _size> temp;
			temp.m_elements[pos] = T(1);
			return temp;
		}
		~Vector() {}
		Vector<T, _size> operator*(const T& a) const
		{
			Vector<T, _size> temp(*this);
			for (size_t i = 0; i < temp.getSize(); i++)
				temp.m_elements[i] *= a;
			return temp;
		}
		Vector<T, _size> operator+(const Vector<T, _size>& b) const
		{
			Vector<T, _size> temp(*this);
			for (size_t i = 0; i < this->getSize(); i++)
				temp[i] = (*this)[i] + b[i];
			return temp;
		}
		Vector<T, _size> operator-(const Vector<T, _size>& b) const
		{
			Vector<T, _size> temp(*this);
			for (size_t i = 0; i < this->getSize(); i++)
				temp.m_elements[i] -= b[i];
			return temp;
		}
		static T Dot(const Vector<T, _size>& a, const Vector<T, _size>& b)
		{
			T result = T(0);
			for (size_t i = 0; i < a.m_vectorSize; i++)
				result += a.m_elements[i] * b.m_elements[i];
			return result;
		}
		size_t getSize() const { return m_vectorSize; }
		T Norm()
		{
			T* result = 0.L;
			for (size_t i = 0; i < this->m_vectorSize; i++)
				result += abs(pow(this->m_elements[i], 2));
			return sqrt(result);
		}
	private:
		T *m_elements;
		size_t m_vectorSize;
	};
}
#endif