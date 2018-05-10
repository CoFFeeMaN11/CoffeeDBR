#include "cml_oneMin.h"
#include <cmath>
#include <cstring>
#include <cassert>
#define H 1e-15L
#define SAMPLING_STEP 1e-2
#define I_LIMIT 10000
IOneMin::IOneMin() : a(0), b(0), maxErr(1e-11), func(0)
{
}
bool IOneMin::InitMethod(long double xStart)
{
	assert(func);
	size_t n = 0;
	long double df;
	a = b = xStart;
	do
	{
		b = a + SAMPLING_STEP*(++n);
		df = Deri(b);
	} while (df < -1e-11  && n < I_LIMIT);
	return n < I_LIMIT;
}

long double IOneMin::Deri(long double x)
{
	long double f1, f2;
	func(x + H, params, f1);
	func(x - H, params, f2);
	return (f1-f2)/(2*H);
}
