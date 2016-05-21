#pragma once
#include "Texture.h"

struct CubeMap : public Texture
{
	int* widths, *heights;
	//Defines blend strength and blend operation with other textures
	
	CubeMap(std::string path, int* widths, int* heights, std::vector<const unsigned char*>& textures);
};
