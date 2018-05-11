#include <iostream>
#include "dbr_parser\dbrParser.h"
#include <complex>
#include <cmath>
#include <cassert>

int main(int argc, char** argv)
{
	DbrParser parser;
	Laser laser1;
	assert(parser.LoadFile("test.dbr"));	
	parser.LoadMaterials(laser1);
	parser.LoadStructure(laser1);
	getchar();
	return 0;
}