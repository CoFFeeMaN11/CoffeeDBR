#ifndef _CML_ONEMIN_H_
#define _CML_ONEMIN_H_
#include <cmath>
class IOneMin
{
public:
	IOneMin();
	virtual ~IOneMin() {};
	void SetFuction(int(*f)(long double, void*, long double&))
	{
		func = f;
	}
	bool NotEnough()
	{
		return abs(a - b) / 2 > maxErr;
	}
	long double GetMin() const
	{
		return minimum;
	}
	void SetParams(void* _param)
	{
		params = _param;
	}
	virtual bool InitMethod(long double xStart);
	virtual void Iterate() = 0;
protected:
	int(*func)(long double, void*, long double&);
	void* params;
	long double a, b, err, maxErr;
	long double minimum;
private:
	long double Deri(long double x);
};
#endif // !_CML_ONEMIN_H_
