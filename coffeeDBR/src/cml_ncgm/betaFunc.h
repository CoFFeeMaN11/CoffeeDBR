#ifndef _BETA_FUNC_H_
#define _BETA_FUNC_H_
#include "../cml_vector/cml_Vector.h"
#include <cassert>
class IBetaFunction
{
public:
	IBetaFunction() : x_n(), x_n1()	{}
	virtual void UpdateData(cml::Vector * const x, size_t tableSize)
	{
		assert(tableSize > 1);
		if (x_n.getSize() == 0)
			x_n.Init(x[0].getSize());
		if (x_n1.getSize() == 0)
			x_n1.Init(x[0].getSize());
		x_n = x[0];
		x_n1 = x[1];
	}
	virtual long double Calc() = 0;
	virtual ~IBetaFunction() {}
protected:
	cml::Vector x_n, x_n1; //x_n1 = x_(n-1)
};
#endif