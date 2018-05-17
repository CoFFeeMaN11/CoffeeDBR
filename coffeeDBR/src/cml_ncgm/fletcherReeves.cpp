#include "fletcherReeves.h"

Fletcher::Fletcher() : IBetaFunction()
{
	
}

long double Fletcher::Calc()
{
	return cml::Vector::Dot(currX,currX)/cml::Vector::Dot(prevX, prevX);
}

Fletcher::~Fletcher()
{
}
