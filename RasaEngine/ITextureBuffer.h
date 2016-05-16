#pragma once
#include <vector>

enum TextureType;

class ITextureBuffer
{
public:
	virtual ~ITextureBuffer(){}

	virtual void setTextureBuffer(const unsigned char* const texture,const int& width, const int& height,TextureType type) = 0;
	virtual void setCubeMapBuffer(std::vector<const unsigned char*>& textures, const int* widths, const int* heights) = 0;
};
