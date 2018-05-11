#ifndef _BETA_FUNC_H_
#define _BETA_FUNC_H_
#include "../cml_vector/cml_Vector.h"
#include <cassert>
class IBetaFunction
{
public:
	IBetaFunction() : x_n(), x_n1()	{}
	virtual void UpdateData(cml::Vector<long double,2> * const x, size_t tableSize)
	{
		x_n = x[0];
		x_n1 = x[1];
	}
	virtual long double Calc() = 0;
	virtual ~IBetaFunction() {}
protected:
	cml::Vector<long double, 2> x_n, x_n1; //x_n1 = x_(n-1)
};
#endif