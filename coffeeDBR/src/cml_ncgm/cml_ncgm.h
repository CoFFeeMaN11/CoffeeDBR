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
	void SetFunction(int (*f)(const cml::Vector&, void*, long double&))
	{
		func = f;
	}
	void SetBetaFunction(eBetaFunction bf);
	const cml::Vector&  GetX() const
	{
		return xvector;
	}
	const cml::Vector&  GetStep() const
	{
		return step;
	}
	const long double GetMinValue() const;
	void SetParams(void * pa)
	{
		params = pa;
	}
	virtual ~ConjugeteGradientSolve();
	bool StartSolve(cml::Vector _startPoint);
	bool Iteration();
private:
	cml::Vector Gradient(cml::Vector point);
	long double Partial(cml::Vector dir, cml::Vector point);
	friend int oneDFunction(long double alpha, void* params, long double& result);
private:
	int (*func)(const cml::Vector&, void*, long double&);
	IBetaFunction *betaF;
	IOneMin *minFinder;
	size_t n;
	void *params;
	long double gradientStep;
	cml::Vector lastDir;
	cml::Vector currDir;
	cml::Vector betaInput[3];
	cml::Vector xvector;
	cml::Vector step;
};
#endif