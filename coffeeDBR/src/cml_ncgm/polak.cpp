#include "polak.h"

Polak::Polak() : IBetaFunction()
{
	
}

long double Polak::Calc()
{
	return cml::Vector::Dot(currX,currX- prevX)/cml::Vector::Dot(prevX, prevX);
}

Polak::~Polak()
{
}
