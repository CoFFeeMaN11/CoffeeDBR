#include "cml_oneMin.h"
#include <cmath>
#include <cstring>
#include <cassert>
#define EXPANSION 1,75
#define STEP 1e-14
#define I_LIMIT 75
IOneMin::IOneMin() : a(0), b(0), maxErr(1e-11), func(0)
{
}
bool IOneMin::InitMethod(long double xStart)
{
	assert(func);
	long double fa, fb, prevA;
	size_t n = 0;
	a = 0;
	b = STEP;
	func(a, params, fa);
	func(b, params, fb);
	if (fb == fa) return true;
	if (fb > fa)
	{
		b = -b;
		func(b, params, fb);
		if (fb >= fa)
		{
			a = b; b = -b;
			return true;
		}
	}
	do
	{
		n++;
		prevA = a;
		a = b;
		b *= EXPANSION;
		func(a, params, fa);
		func(b, params, fb);
	} while (fa > fb && n < I_LIMIT);
	if (n < I_LIMIT)
	{
		if (prevA < b)
			a = prevA;
		else
		{
			a = b; b = prevA;
		}
	}
	return n < I_LIMIT;
}

