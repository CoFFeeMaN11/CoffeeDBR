#include "laserParams.h"

void LaserParams::SetVaweParams(VaweParams x)
{
	vaweParams = x;
}

void LaserParams::SetModFinderParams(ModFinderParams x)
{
	modFinderParams = x;
}

const VaweParams & LaserParams::GetVaweParams() const
{
	return vaweParams;
}

const ModFinderParams & LaserParams::GetModFinderParams() const
{
	return modFinderParams;
}
