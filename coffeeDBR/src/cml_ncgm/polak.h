#ifndef _POLAK_H_
#define _POLAK_H_
#include "betaFunc.h"
class Polak : public IBetaFunction
{
public:
	Polak();
	virtual long double Calc();
	virtual ~Polak();
};
#endif