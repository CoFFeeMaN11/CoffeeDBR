#include "cml_Vector.h"
#include <assert.h>
#include <cstring>
#include <cmath>
#include <Windows.h>
#define ABS(x) x > 0 ? x : -x
#define MIN(x,y) x>y ? y : x
cml::Vector::Vector() : m_elements(0), m_vectorSize(0) {}
cml::Vector::Vector(const size_t vectorSize) : m_vectorSize(vectorSize)
{
	m_elements = new long double[vectorSize];
	ZeroMemory(m_elements, vectorSize * sizeof(long double));
}

cml::Vector::Vector(const Vector& vec)
{
	this->m_elements = new long double[vec.getSize()];
	for (int i = 0; i < vec.getSize(); i++)
		m_elements[i] = vec[i];
	m_vectorSize = vec.m_vectorSize;
}

cml::Vector cml::Vector::Unit(const size_t vectorSize, size_t pos)
{
	cml::Vector temp(vectorSize);
	temp[pos] = 1.L;
	return temp;
}

long double& cml::Vector::operator[](const size_t index)
{
	assert(index < m_vectorSize);
	return m_elements[index];
}
const long double& cml::Vector::operator[](const size_t index) const
{
	assert(index < m_vectorSize);
	return m_elements[index];
}
long double cml::Vector::Norm()
{
	long double result = 0.L;
	for(size_t i = 0; i < this->m_vectorSize; i++)
		result += pow(this->m_elements[i], 2);
	return sqrt(result);
}
cml::Vector::operator cml::ComplexVector()
{
	cml::ComplexVector ret(m_vectorSize);
	for (int i = 0; i < m_vectorSize; i++)
		ret[i] = complex(m_elements[i]);
	return ret;
}
long double cml::Vector::Dot(const cml::Vector& a, const cml::Vector& b)
{
	assert(a.m_vectorSize == b.m_vectorSize);
	long double result = 0.L;
	for(size_t i = 0; i < a.m_vectorSize; i++)
		result += a[i]*b[i];
	return result;
}
cml::Vector cml::Vector::operator*(const long double& a) const
{
	cml::Vector temp(*this);
	for(size_t i = 0; i < temp.getSize(); i++)
		temp[i] *= a;
	return temp;
}
cml::Vector cml::Vector::operator+(const cml::Vector& b) const
{
	assert(this->getSize() == b.getSize());
	cml::Vector temp(*this);
	for(size_t i = 0; i < this->getSize(); i++)
		temp[i]= (*this)[i] + b[i];
	return temp;
}
cml::Vector cml::Vector::operator-(const cml::Vector& b) const
{
	assert(this->getSize() == b.getSize());
	cml::Vector temp(*this);
	for(size_t i = 0; i < this->getSize(); i++)
		temp[i]-= b[i];
	return temp;
}
cml::Vector cml::Vector::operator=(const cml::Vector & b)
{
	if (!m_elements) {
		m_elements = new long double[b.m_vectorSize];
		m_vectorSize = b.m_vectorSize;
	}
	assert(b.m_vectorSize == this->m_vectorSize);
	memcpy(m_elements, b.m_elements, sizeof(long double)*b.m_vectorSize);
	return *this;
}
cml::Vector::~Vector()
{
	if(this->m_elements)
	{
		delete [] this->m_elements;
		this->m_elements = 0;
	}
}
void cml::Vector::Init(size_t size)
{
	assert(!m_elements && m_vectorSize == 0);
	m_elements = new long double[size];
	m_vectorSize = size;
}
void cml::Vector::Insert(long double* tab, size_t start, size_t size)
{
	memcpy(this->m_elements,tab+start,sizeof(long double)*MIN(size,start-this->getSize()-1));
}

cml::Vector operator*(const long double & a, const cml::Vector & b)
{
	cml::Vector ret(b);
	for (int i = 0; i < b.getSize(); i++)
		ret[i] *= a;
	return ret;
}

cml::ComplexVector::ComplexVector() : m_elements(0), m_vectorSize(0)
{
}

cml::ComplexVector::ComplexVector(const size_t vectorSize) : m_vectorSize(vectorSize)
{
	m_elements = new complex[m_vectorSize];
	ZeroMemory(m_elements, vectorSize * sizeof(complex));
}

cml::ComplexVector::ComplexVector(const ComplexVector & vec)
{
	m_elements = new complex[vec.m_vectorSize];
	m_vectorSize = vec.m_vectorSize;
	memcpy(m_elements, vec.m_elements, m_vectorSize);
}

cml::ComplexVector::~ComplexVector()
{
	if (m_elements)
	{
		delete[] m_elements;
		m_elements = 0;
		m_vectorSize = 0;
	}
}

void cml::ComplexVector::Init(size_t size)
{
	m_elements = new complex[size];
	m_vectorSize = size;
}

cml::complex & cml::ComplexVector::operator[](size_t index)
{
	assert(index < m_vectorSize);
	return m_elements[index];
}

const cml::complex & cml::ComplexVector::operator[](size_t index) const
{
	assert(index < m_vectorSize);
	return m_elements[index];
}