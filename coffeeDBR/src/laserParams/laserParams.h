#ifndef _LASER_PARAMS_H_
#define _LASER_PARAMS_H_
struct  VaweParams
{
	long double startLength;
	long double stopLength;
	long double step;
};
struct ModFinderParams
{
	long double resuduum;
	size_t fuse;
};
class LaserParams
{
public:
	LaserParams()
	{

	}
	~LaserParams()
	{

	}
	void SetVaweParams(VaweParams);
	void SetModFinderParams(ModFinderParams);
	const VaweParams& GetVaweParams() const;
	const ModFinderParams& GetModFinderParams() const;
private:
	VaweParams vaweParams;
	ModFinderParams modFinderParams;
};
#endif // !_LASER_PARAMS_H_
