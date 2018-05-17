#include "cml_matrix2.h"
#include <cstring>
#include <cassert>
#include <Windows.h>
cml::Matrix2::Matrix2()
{
	ZeroMemory(m_elements, sizeof(cml::complex) * 4);
}

cml::Matrix2::Matrix2(cml::complex a11, cml::complex a12, cml::complex a21, cml::complex a22)
{
	this->m_elements[0] = a11;
	this->m_elements[1] = a12;
	this->m_elements[2] = a21;
	this->m_elements[3] = a22;
}

cml::Matrix2::Matrix2(const Matrix2& mat)
{
	memcpy(m_elements,mat.m_elements, sizeof(cml::complex)*4);
}

cml::Matrix2::~Matrix2()
{

}
cml::Matrix2 cml::Matrix2::Identity()
{
	return cml::Matrix2(cml::complex(1), cml::complex(0), cml::complex(0), cml::complex(1));
}

const cml::complex& cml::Matrix2::operator[](size_t index) const
{
	assert(index < 4);
	return this->m_elements[index];
}
cml::complex& cml::Matrix2::operator[](size_t index)
{
	assert(index < 4);
	return this->m_elements[index];
}
cml::Matrix2 operator*(const cml::Matrix2& a,const cml::Matrix2& b)
{
	cml::complex a11 = a[0]*b[0]+a[1]*b[2];
	cml::complex a12 = a[0]*b[1]+a[1]*b[3];
	cml::complex a21 = a[2]*b[0]+a[3]*b[2];
	cml::complex a22 = a[2]*b[1]+a[3]*b[3];
	return cml::Matrix2(a11,a12,a21,a22);
}
cml::Matrix2 operator*(const long double & a, const cml::Matrix2 & b)
{
	cml::Matrix2 ret = cml::Matrix2::Identity();
	for(int i = 0; i < 4; i++)
		ret[i] = cml::complex(a)*b[i];
	return ret;
}
cml::Matrix2 cml::Matrix2::operator*=(const cml::Matrix2 &a)
{
	/*m_elements[0] = a[0] * m_elements[0] + a[1] * m_elements[2];
	m_elements[1] = a[0] * m_elements[1] + a[1] * m_elements[3];
	m_elements[2] = a[2] * m_elements[0] + a[3] * m_elements[2];
	m_elements[3] = a[2] * m_elements[1] + a[3] * m_elements[3];*/
	*this = a * *this;
	return *this;
}
cml::ComplexVector cml::Matrix2::operator*(const ComplexVector& vec)
{
	assert(vec.getSize() == 2);
	cml::ComplexVector temp(2);
	cml::Matrix2 a(*this);
	temp[0] = a[0]*vec[0]+a[1]*vec[1];
	temp[1] = a[2]*vec[0]+a[3]*vec[1];
	return temp;
}