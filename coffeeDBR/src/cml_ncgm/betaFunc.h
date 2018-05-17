#ifndef _BETA_FUNC_H_
#define _BETA_FUNC_H_
#include "../cml_vector/cml_Vector.h"
#include <cassert>
class IBetaFunction
{
public:
	IBetaFunction() : currX(), prevX()	{}
	virtual void UpdateData(cml::Vector * const x, size_t tableSize)
	{
		assert(tableSize > 1);
		if (currX.getSize() == 0)
			currX.Init(x[0].getSize());
		if (prevX.getSize() == 0)
			prevX.Init(x[0].getSize());
		currX = x[0];
		prevX = x[1];
	}
	virtual long double Calc() = 0;
	virtual ~IBetaFunction() {}
protected:
	cml::Vector currX, prevX; //x_n1 = x_(n-1)
};
#endif