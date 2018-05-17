#include "laser.h"
#include <cassert>
Laser::Laser()
{
	materials.clear();
	laserStruct.clear();
}

Laser::~Laser()
{
	materials.clear();
	laserStruct.clear();
}

void Laser::AddMaterial(const Material & material)
{
	assert(materials.find(material.id) == materials.end());
	materials.insert(std::pair<unsigned char, Material>(material.id, material));
}

void Laser::AddLayer(unsigned char matId, long double thinkess)
{
	if (thinkess < 0)
	{
		assert(materials.find(matId) != materials.end());
		thinkess = materials[matId].thinkess;
	}
	laserStruct.push_back(std::pair<unsigned char, long double>(matId, thinkess));
}

size_t Laser::GetStructSize()
{
	return laserStruct.size();
}

Material Laser::GetMaterial(size_t layerid)
{
	Material ret = materials[laserStruct[layerid].first];
	ret.thinkess = laserStruct[layerid].second;
	return ret;
}
