#ifndef _CML_GOLDEN_H_
#define _CML_GOLDEN_H_
#include "cml_oneMin.h"
class GoldenSec : public IOneMin
{
public:
	GoldenSec() : IOneMin(){}
	virtual ~GoldenSec() {}
	virtual void Iterate();
	virtual bool InitMethod(long double xStart);
private:
	long double xL, xR;
	
};
#endif // !_CML_GOLDEN_H_
