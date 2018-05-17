#include "dbr_field.h"
#include <algorithm>
#include <iostream>
#define PI 3.1415926535897932L
#define IM_UNIT std::complex<long double>(0,1)

int _FindMod(const cml::Vector& in, void* params, long double& out)
{
	DbrField* dbr = (DbrField*)params;
	cml::Matrix2 mirror = dbr->GetMirrorMatrix(COMPLEX_N(in[0], in[1]));
	out = std::abs(mirror[3]);
	return 0;
}

struct mod_compare : public std::unary_function<COMPLEX_N, bool>
{
	explicit mod_compare(const COMPLEX_N &_base, long double res) : base(_base), resuduum(res){}
	bool operator() (const COMPLEX_N& arg)
	{
		return std::abs(base.real() - arg.real()) < 1e-3;
	}
	COMPLEX_N base;
	long double resuduum;
};

cml::Matrix2 DbrField::GetMirrorMatrix(std::complex<long double> vaweleght)
{
	
	const COMPLEX_N air_k = std::complex<long double>(2 * PI) / vaweleght;
	
	lastVawe = vaweleght;
	mirror = cml::Matrix2::Identity();
	cml::Matrix2 GMatrix, LMatrix;

	COMPLEX_N h(0, 0);

	COMPLEX_N prevK = air_k;
	COMPLEX_N currK;

	Material currMaterial;
	for (size_t i = 0; i < laser->GetStructSize(); i++)
	{
		//Macierz przejœcia przez granicê oœrodków
		currMaterial = laser->GetMaterial(i);
		currK = air_k * COMPLEX_N(currMaterial.refIndexRe, currMaterial.refIndexIm);
		GMatrix[0] = COMPLEX_N(0.5)*(std::complex<long double>(1.0L)  + prevK / currK);
		GMatrix[1] = COMPLEX_N(0.5)* (std::complex<long double>(1.0L) - prevK / currK);
		GMatrix[2] = GMatrix[1];
		GMatrix[3] = GMatrix[0];
		//Macierz propagacji
		LMatrix[0] = std::exp(IM_UNIT * currK * currMaterial.thinkess);
		LMatrix[3] = std::exp(-IM_UNIT * currK * currMaterial.thinkess);

		mirror *=  LMatrix*GMatrix;
		prevK = currK;
	}
	GMatrix[0] = COMPLEX_N(0.5)*(std::complex<long double>(1.0L) + prevK / air_k);
	GMatrix[1] = COMPLEX_N(0.5)* (std::complex<long double>(1.0L) - prevK / air_k);
	GMatrix[2] = GMatrix[1];
	GMatrix[3] = GMatrix[0];
	mirror *= GMatrix;
	return mirror;
}

COMPLEX_N DbrField::FindMod(LaserParams & params, std::vector<COMPLEX_N>& out)
{
	ConjugeteGradientSolve cgs(2);
	cgs.SetFunction(_FindMod);
	cgs.SetParams(this);
	cgs.SetBetaFunction(eBetaFunction::FletcherReeves);
	cml::Vector startPoint(2);
	ModFinderParams finderParams = params.GetModFinderParams();
	COMPLEX_N result;
	size_t n = 0;

	for (long double lambda = params.GetVaweParams().startLength;
		lambda <= params.GetVaweParams().stopLength; lambda += params.GetVaweParams().step)
	{
		n = 0;
		std::cout << "\nSzukanie moda dla: " << lambda << " nm\n";
		startPoint[0] = lambda; startPoint[1] = 0;
		if (!cgs.StartSolve(startPoint)) continue;
		do
		{
			n++;
			if (!cgs.Iteration() || cgs.GetMinValue() > 100.L) n = finderParams.fuse;
		} while (cgs.GetMinValue() > finderParams.resuduum && n < finderParams.fuse);
		if (n < finderParams.fuse)
		{
			std::cout << "Znalesiono minimum\n";
			printf("%f%+fi\n", cgs.GetX()[0], cgs.GetX()[1]);
			result = COMPLEX_N(cgs.GetX()[0], cgs.GetX()[1]);
			
			if ((std::find_if(out.begin(), out.end(), mod_compare(result, finderParams.resuduum * 10)) == out.end()) &&
				result.real() >= laserParams.GetVaweParams().startLength && result.real() <= laserParams.GetVaweParams().stopLength)
			{
				out.push_back(result);
				std::cout << "\nZnalesiono mod\n";
				printf("%f%+fi\n\n", cgs.GetX()[0], cgs.GetX()[1]);
				
			}	
		}
		else
		{
		}

	}


	return COMPLEX_N();
}

