#include "cml_matrix2.h"
#include <cstring>
#include <cassert>

cml::Matrix2::Matrix2(long double a11,long double a12,long double a21,long double a22)
{
	this->m_elements[0] = a11;
	this->m_elements[1] = a12;
	this->m_elements[2] = a21;
	this->m_elements[3] = a22;
}

cml::Matrix2::Matrix2(const Matrix2& mat)
{
	memcpy(m_elements,mat.m_elements, sizeof(long double)*4);
}

cml::Matrix2::~Matrix2()
{

}
cml::Matrix2 cml::Matrix2::Identity()
{
	return cml::Matrix2(1,0,0,1);
}

const long double& cml::Matrix2::operator[](size_t index) const
{
	assert(index < 4);
	return this->m_elements[index];
}
long double& cml::Matrix2::operator[](size_t index)
{
	assert(index < 4);
	return this->m_elements[index];
}
cml::Matrix2 cml::Matrix2::operator*(const Matrix2& b)
{
	cml::Matrix2 a(*this);
	long double a11 = a[0]*b[0]+a[1]*b[2];
	long double a12 = a[0]*b[1]+a[1]*b[3];
	long double a21 = a[2]*b[0]+a[3]*b[2];
	long double a22 = a[2]*b[1]+a[3]*b[3];
	return cml::Matrix2(a11,a12,a21,a22);
}
cml::Vector cml::Matrix2::operator*(const Vector& vec)
{
	assert(vec.getSize() == 2);
	cml::Vector temp(2);
	cml::Matrix2 a(*this);
	temp[0] = a[0]*vec[0]+a[1]*vec[1];
	temp[1] = a[2]*vec[0]+a[3]*vec[1];
	return temp;
}