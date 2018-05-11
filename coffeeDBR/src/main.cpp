#include <iostream>
#include "dbr_parser\dbrParser.h"
#include "cml_vector\cml_Vector.h"
#include "cml_ncgm\cml_ncgm.h"
#include <complex>
#include <cmath>
#include <cassert>

int testFunc(const cml::Vector<long double, 2>& in, void*, long double& out)
{
	std::complex<long double> x(in[0], in[1]);
	out = abs((pow(x, 2) + std::complex<long double>(1L))*std::complex<long double>(1));
	return 0;
}
int main(int argc, char** argv)
{
	DbrParser parser;
	Laser laser1;
	assert(parser.LoadFile("test.dbr"));	
	parser.LoadMaterials(laser1);
	parser.LoadStructure(laser1);
	ConjugeteGradientSolve solver(2);
	solver.SetFunction(testFunc);
	cml::Vector<long double, 2>a, b;
	a[0] = 1; a[1] = 2;
	b[0] = 3; b[1] = 1;
	cml::Vector<long double, 2> test = a + (b * 2.L);
	cml::Vector<long double, 2> start;
	start[0] = -3; start[1] = 0.3;
	int n = 0;
	solver.StartSolve(start);
	do
	{
		n++;
		solver.Iteration();
	} while (solver.GetMinValue() > 1e-11 && n < 10000);
	std::cout << "N=" << n << '\n';
	printf("%f %f\n", solver.GetX()[0], solver.GetX()[1]);
	getchar();
	return 0;
}