#include "cml_golden.h"
#include <cassert>
#define GOLDEN_RADIO 0.6180339887498949L
void GoldenSec::Iterate()
{
	assert(func);
	long double fL, fR;
	func(xL, params, fL);
	func(xR, params, fR);
	if (fL < fR)
	{
		b = xR;
		xR = xL;
		xL = b - GOLDEN_RADIO * (b - a);
	}
	else
	{
		a = xL;
		xL = xR;
		xR = a + GOLDEN_RADIO * (b - a);
	}
	minimum = (a + b) / 2;
}

bool GoldenSec::InitMethod(long double xStart)
{
	if(!IOneMin::InitMethod(xStart))
		return false;
	xL = b - GOLDEN_RADIO * (b - a);
	xR = a + GOLDEN_RADIO * (b - a);
	return true;
}
