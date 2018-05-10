#ifndef _FLET_REEV_H_
#define _FLET_REEV_H_
#include "betaFunc.h"
class Fletcher : public IBetaFunction
{
public:
	Fletcher();
	virtual long double Calc();
	virtual ~Fletcher();
};
#endif