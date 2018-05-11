#include "cml_ncgm.h"
#include <cstdio>
int oneDFunction(long double alpha, void* params, long double& result)
{
	ConjugeteGradientSolve *cgs = (ConjugeteGradientSolve*)params;
	cml::Vector<long double, 2> t = (cgs->GetStep() * alpha);
	cgs->func(cgs->GetX() + t, cgs->params, result);
	return 0;
}

ConjugeteGradientSolve::ConjugeteGradientSolve(size_t xSize) : params(0), xvector(), func(0),
																gradientStep(1e-11), lastDir(), currDir(),step(), n(2), betaF(0), minFinder(0)
{
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

void ConjugeteGradientSolve::StartSolve(cml::Vector<long double, 2> _startPoint)
{
	if(!betaF)
		betaF = new Fletcher();
	if(!minFinder)
		minFinder = new GoldenSec();

	cml::Vector<long double, 2> direction = this->Gradient(_startPoint)* -1.L;
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
	assert(n < 1000);
	long double mini = minFinder->GetMin();
	this->xvector = _startPoint + direction * mini;
}

void ConjugeteGradientSolve::Iteration()
{
	cml::Vector<long double, 2> currDir =  this->Gradient(this->xvector)* -1.L;
	betaInput[0] = currDir;
	betaInput[1] = lastDir;
	betaInput[2] = step;
	this->betaF->UpdateData(betaInput, 3);
	long double beta = betaF->Calc();
	step = currDir + (step * beta);
	int n = 0;
	minFinder->InitMethod(0L);
	do
	{
		minFinder->Iterate();
	} while (minFinder->NotEnough() && ++n < 1000 );
	assert(n < 1000);
	xvector = xvector + step * minFinder->GetMin();
}

cml::Vector<long double, 2> ConjugeteGradientSolve::Gradient(cml::Vector<long double, 2> point)
{	
	cml::Vector<long double, 2> result;
	for (int i = 0; i < 2; i++)
		result[i] = Partial(cml::Vector<long double, 2>::Unit(i), point);
	return result;
}

long double ConjugeteGradientSolve::Partial(cml::Vector<long double, 2> dir, cml::Vector<long double, 2> point)
{
	assert(func);
	long double f1, f2;
	assert(!func(point + (dir * gradientStep), params, f1));
	assert(!func(point,params, f2));
	return (f1 - f2)/(gradientStep);
}


