#include "dbrParser.h"
#include <stdlib.h>
#include <sstream>
#include <cassert>
void ParseStruElem(const std::string& str, unsigned char& id, long double& thinkess)
{
	size_t pos = str.find(':');
	if (pos == std::string::npos)
	{
		id = atoi(str.c_str());
		thinkess = -1L;
	}
	else
	{
		std::string buff = str.substr(0, pos);
		id = atoi(str.substr(0,pos).c_str());
		thinkess = atof(str.substr(pos + 1).c_str());
	}
}

bool DbrParser::LoadFile(const std::string& filepath)
{
	pugi::xml_parse_result result = file.load_file(filepath.c_str());
	if (result)
	{
		mainNode = file.child("DBR");
		return mainNode;
	}
	return false;
}

void DbrParser::LoadMaterials(Laser& laser)
{
	pugi::xml_node buffer, materialsNode = mainNode.child("materials");
	Material temp;
	buffer = materialsNode.child("material");
	do
	{
		temp.id = buffer.attribute("id").as_uint();
		temp.name = buffer.attribute("name").as_string();
		temp.refIndexRe = buffer.attribute("refReal").as_double();
		temp.refIndexIm = buffer.attribute("refIm").as_double();
		temp.thinkess = buffer.attribute("thickness").as_double();
		laser.AddMaterial(temp);
	} while ((buffer = buffer.next_sibling("material")));
}

void DbrParser::LoadStructure(Laser & laser)
{
	pugi::xml_node structNode = mainNode.child("structure");
	assert(structNode);
	std::string buffer = structNode.first_child().value();
	std::stringstream ss;
	ss.str(buffer);
	unsigned char id;
	long double thinkness;
	while (ss >> buffer)
	{
		ParseStruElem(buffer, id, thinkness);
		laser.AddLayer(id, thinkness);
	}
}
