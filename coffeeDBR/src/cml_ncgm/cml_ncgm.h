#ifndef _CML_NCGM_H_
#define _CML_NCGM_H_
#include "../cml_vector/cml_Vector.h"
#include <cassert>
#include "betaFuncs.h"
#include "../cml_oneMin/cml_golden.h"
class ConjugeteGradientSolve
{
public:
	
	ConjugeteGradientSolve(size_t xSize);
	void SetFunction(int (*f)(const cml::Vector<long double,2>&, void*, long double&))
	{
		func = f;
	}
	const cml::Vector<long double, 2>&  GetX() const
	{
		return xvector;
	}
	const cml::Vector<long double, 2>&  GetStep() const
	{
		return step;
	}
	const long double GetMinValue() const;
	void* GetParams() const
	{
		return params;
	}
	virtual ~ConjugeteGradientSolve();
	void StartSolve(cml::Vector<long double, 2> _startPoint);
	void Iteration();
private:
	cml::Vector<long double, 2> Gradient(cml::Vector<long double, 2> point);
	long double Partial(cml::Vector<long double, 2> dir, cml::Vector<long double, 2> point);
	friend int oneDFunction(long double alpha, void* params, long double& result);
private:
	int (*func)(const cml::Vector<long double, 2>&, void*, long double&);
	IBetaFunction *betaF;
	IOneMin *minFinder;
	size_t n;
	void *params;
	long double gradientStep;
	cml::Vector<long double, 2> lastDir;
	cml::Vector<long double, 2> currDir;
	cml::Vector<long double, 2> betaInput[3];
	cml::Vector<long double, 2> xvector;
	cml::Vector<long double, 2> step;
};
#endif