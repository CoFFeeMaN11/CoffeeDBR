#include "hestenes.h"

Hestenes::Hestenes(): IBetaFunction(), prevStep()
{
}

void Hestenes::UpdateData(cml::Vector * const x, size_t tableSize)
{
	IBetaFunction::UpdateData(x, tableSize);
	prevStep = x[2];
}

long double Hestenes::Calc()
{
	return -cml::Vector::Dot(currX,currX-prevX)/ cml::Vector::Dot(prevStep, currX - prevX);
}

Hestenes::~Hestenes()
{
}
