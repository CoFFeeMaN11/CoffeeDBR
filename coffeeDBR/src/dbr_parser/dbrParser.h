#ifndef _DBR_PARSER_H_
#define _DBR_PARSER_H_
#include <cstring>
#include "../pugixml/pugixml.hpp"
#include "../pugixml/pugiconfig.hpp"
#include "../laser/laser.h"
#include "../laserParams/laserParams.h"
class DbrParser
{
public:
	DbrParser() : file()
	{
		
	}
	bool LoadFile(const std::string& filepath);
	void LoadMaterials(Laser& laser);
	void LoadStructure(Laser& laser);
	void LoadParams(LaserParams& params);
private:
	pugi::xml_document file;
	pugi::xml_node mainNode;
};
#endif // !_DBR_PARSER_H_
