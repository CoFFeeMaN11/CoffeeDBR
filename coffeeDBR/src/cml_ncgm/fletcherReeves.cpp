#include "fletcherReeves.h"

Fletcher::Fletcher() : IBetaFunction()
{
	
}

long double Fletcher::Calc()
{
	return cml::Vector<long double, 2>::Dot(x_n,x_n)/cml::Vector<long double, 2>::Dot(x_n1, x_n1);
}

Fletcher::~Fletcher()
{
}
