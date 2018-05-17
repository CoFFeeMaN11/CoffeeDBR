#include "cml_ncgm.h"
#include <cstdio>
int oneDFunction(long double alpha, void* params, long double& result)
{
	ConjugeteGradientSolve *cgs = (ConjugeteGradientSolve*)params;
	cml::Vector t = (alpha*cgs->GetStep());
	cgs->func(cgs->GetX() + t, cgs->params, result);
	return 0;
}

ConjugeteGradientSolve::ConjugeteGradientSolve(size_t xSize) : params(0), xvector(xSize), func(0),
																gradientStep(1e-10), lastDir(xSize), currDir(xSize),step(xSize), n(2), betaF(0), minFinder(0)
{
}

void ConjugeteGradientSolve::SetBetaFunction(eBetaFunction bf)
{
	if (betaF)
		delete betaF;
	betaF = getBeta(bf);
}


const long double ConjugeteGradientSolve::GetMinValue() const
{
	long double result;
	func(xvector, params, result);
	return result;
}

ConjugeteGradientSolve::~ConjugeteGradientSolve()
{
	if (betaF)
	{
		delete betaF;
		betaF = 0;
	}
	if (minFinder)
	{
		delete minFinder;
		minFinder = 0;
	}
}

bool ConjugeteGradientSolve::StartSolve(cml::Vector _startPoint)
{
	assert(betaF);
	if(!minFinder)
		minFinder = new GoldenSec();

	cml::Vector direction = -1.L*this->Gradient(_startPoint);
	lastDir = direction;
	step = direction;

	minFinder->SetFuction(oneDFunction);
	minFinder->SetParams(this);
	minFinder->InitMethod(0L);
	int n = 0;
	do
	{
		minFinder->Iterate();
	} while (minFinder->NotEnough() && ++n <1000);
	if (n > 1000) return false;
	long double mini = minFinder->GetMin();
	this->xvector = _startPoint + mini*direction;
	return true;
}

bool ConjugeteGradientSolve::Iteration()
{
	cml::Vector currDir = -1.L*this->Gradient(this->xvector);
	betaInput[0] = currDir;
	betaInput[1] = lastDir;
	betaInput[2] = step;
	this->betaF->UpdateData(betaInput, 3);
	long double beta = betaF->Calc();
	step = currDir + (beta*step);
	int n = 0;
	if(!minFinder->InitMethod(0L)) return false;
	do
	{
		minFinder->Iterate();
	} while (minFinder->NotEnough() && ++n < 1000 );
	if (n > 1000) return false;
	xvector = xvector + minFinder->GetMin()*step;
	return true;
}

cml::Vector ConjugeteGradientSolve::Gradient(cml::Vector point)
{	
	cml::Vector result(n);
	for (int i = 0; i < n; i++)
		result[i] = Partial(cml::Vector::Unit(n, i), point);
	return result;
}

long double ConjugeteGradientSolve::Partial(cml::Vector dir, cml::Vector point)
{
	assert(func);
	long double f0, f1, f3, f4;
	assert(!func(point - (2.L*gradientStep* dir), params, f0));
	assert(!func(point - gradientStep* dir, params, f1));
	assert(!func(point + gradientStep* dir, params, f3));
	assert(!func(point + 2.L*gradientStep*dir, params, f4));
	return (f0 - f4 + 8.L*(f3 - f1)) / (12 * gradientStep);
}


