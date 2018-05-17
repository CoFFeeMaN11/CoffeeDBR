#ifndef _DBR_FIELD_H_
#define _DBR_FIELD_H_
#include "../laser/laser.h"
#include "../laserParams/laserParams.h"
#include "../cml_matrix2/cml_matrix2.h"
#include "../cml_ncgm/cml_ncgm.h"
#include <vector>
#include <complex>
#define COMPLEX_N std::complex<long double>
class DbrField
{
public:
	cml::Matrix2 GetMirrorMatrix(std::complex<long double> vaweleght);
	COMPLEX_N FindMod(LaserParams& params,std::vector<COMPLEX_N>& out);
	void SetLaserStruct(Laser * _laser)
	{
		laser = _laser;
	}
private:
	Laser * laser;
	COMPLEX_N lastVawe;
	cml::Matrix2 mirror;
	LaserParams laserParams;

};
#endif // !_DBR_FIELD_H_
