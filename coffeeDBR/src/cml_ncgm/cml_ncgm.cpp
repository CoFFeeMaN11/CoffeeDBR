#include "cml_ncgm.h"
#include <cstdio>
int oneDFunction(long double alpha, void* params, long double& result)
{
	ConjugeteGradientSolve *cgs = (ConjugeteGradientSolve*)params;
	cml::Vector t = (cgs->GetStep() * alpha);
	cgs->func(cgs->GetX() + t, cgs->params, result);
	return 0;
}

ConjugeteGradientSolve::ConjugeteGradientSolve(size_t xSize) : params(0), xvector(xSize), func(0),
																gradientStep(1e-15), lastDir(xSize), currDir(xSize),step(xSize), n(2), betaF(0), minFinder(0)
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

void ConjugeteGradientSolve::StartSolve(cml::Vector _startPoint)
{
	if(!betaF)
		betaF = new Fletcher();
	if(!minFinder)
		minFinder = new GoldenSec();

	cml::Vector direction = this->Gradient(_startPoint)* -1.L;
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
	printf("%f\t%f\n", direction[0], direction[1]);
	this->xvector = _startPoint + direction * mini;
}

void ConjugeteGradientSolve::Iteration()
{
	cml::Vector currDir =  this->Gradient(this->xvector)* -1.L;
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
	 
	printf("ls: %f %fi\n", lastDir[0], lastDir[1]);
	printf("cs: %f %fi\n\n", currDir[0], currDir[1]);
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
	long double f1, f2;
	assert(!func(point + dir * gradientStep, params, f1));
	assert(!func(point - dir * gradientStep,params, f2));
	return (f1 - f2)/(2 * gradientStep);
}


