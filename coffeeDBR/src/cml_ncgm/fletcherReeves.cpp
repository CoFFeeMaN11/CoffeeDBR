#include "fletcherReeves.h"

Fletcher::Fletcher() : IBetaFunction()
{
	
}

long double Fletcher::Calc()
{
	return cml::Vector::Dot(x_n,x_n)/cml::Vector::Dot(x_n1, x_n1);
}

Fletcher::~Fletcher()
{
}
