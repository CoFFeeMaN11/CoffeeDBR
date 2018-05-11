#ifndef _LASER_H_H_
#define _LASER_H_H_
#include <complex>
#include <string>
#include <list>
#include <map>
struct Material
{
	unsigned char id;
	std::string name;
	long double refIndexRe, refIndexIm;
	long double thinkess;
};
class Laser
{
public:
	Laser();
	~Laser();
	void AddMaterial(const Material& material);
	void AddLayer(unsigned char matId, long double thinkess = -1.0L);
private:
	std::map<unsigned char, Material> materials;
	std::list < std::pair<unsigned char, long double> > laserStruct;
};
#endif // !_LASER_H_H_
