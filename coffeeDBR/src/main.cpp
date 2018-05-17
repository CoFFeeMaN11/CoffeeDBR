#include <iostream>
#include "cml_ncgm\cml_ncgm.h"
#include <complex>
#include <cmath>
#include "cml_matrix2\cml_matrix2.h"
#include "dbr_field\dbr_field.h"
#include "dbr_parser\dbrParser.h"
#include "laserParams\laserParams.h"

int test(const cml::Vector& in, void* params, long double& out)
{
	std::complex<long double> x(in[0], in[1]);
	x = std::pow(x, 2);
	out = std::abs(x + std::complex<long double>(1, 0));
	return 0;
}
int main(int argc, char** argv)
{
	DbrField dbr;
	Laser laser;
	DbrParser parser;
	LaserParams params;
	std::vector<std::complex<long double>> mods;
	assert(parser.LoadFile("test.dbr"));
	parser.LoadMaterials(laser);
	parser.LoadStructure(laser);
	parser.LoadParams(params);
	dbr.SetLaserStruct(&laser);
	dbr.FindMod(params, mods);
	std::cout << "\nZnaleziono w sumie " << mods.size() << " modow\n";
	getchar();
	return 0;
}