#include <iostream>
#include "cml_ncgm\cml_ncgm.h"
#include <complex>
#include <cmath>

int test(const cml::Vector& in, void* params, long double& out)
{
	std::complex<long double> x(in[0], in[1]);
	out = abs(pow(x, 2) + std::complex<long double>(1, 0));
	return 0;
}
int main(int argc, char** argv)
{
	ConjugeteGradientSolve solver(2);
	solver.SetFunction(test);
	cml::Vector start(2);
	start[0] = -0.5L;
	start[1] = 1.5L;
	solver.StartSolve(start);
	cml::Vector b(2);
	b[0] = 2; b[1] = 3;
	cml::Vector a = b * 0.02L;
	
	int n = 0;
	do
	{
		n++;
		solver.Iteration();
	} while (solver.GetMinValue() > 1e-11 && n < 1000);
	printf("N= %d\n", n);
	a = solver.GetX();
	printf("x= %f%+fi\n", a[0], a[1]);
	getchar();
	return 0;
}