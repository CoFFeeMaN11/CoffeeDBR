#ifndef _HESTENES_H_
#define _HESTENES_H_
#include "betaFunc.h"
class Hestenes : public IBetaFunction
{
public:
	Hestenes();
	virtual void UpdateData(cml::Vector * const x, size_t tableSize) override;
	virtual long double Calc() override;
	virtual ~Hestenes();
private:
	cml::Vector prevStep;
};
#endif // !_HESTENES_H_
