#include "CubeMap.h"
#include "Context.h"

CubeMap::CubeMap(std::string path, int* widths, int* heights, std::vector<const unsigned char*>& textures)
{
	this->path = path;
	this->textureBuffer = Context::getInstance().CreateTextureBuffer(textures, widths, heights);
	this->type = TextureType_CUBEMAP;
	this->widths = widths;
	this->heights = heights;
}