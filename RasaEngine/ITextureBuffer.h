#pragma once
#include <vector>
using namespace std;

enum BufferedTextureType
{
	BufferedTextureType_NONE = 0x0, BufferedTextureType_DIFFUSE = 0x1, BufferedTextureType_SPECULAR = 0x2, BufferedTextureType_AMBIENT = 0x3,
	BufferedTextureType_EMISSIVE = 0x4, BufferedTextureType_HEIGHT = 0x5, BufferedTextureType_NORMALS = 0x6, BufferedTextureType_SHININESS = 0x7,
	BufferedTextureType_OPACITY = 0x8, BufferedTextureType_DISPLACEMENT = 0x9, BufferedTextureType_LIGHTMAP = 0xA, BufferedTextureType_REFLECTION = 0xB,
	BufferedTextureType_UNKNOWN = 0xC
};

class ITextureBuffer
{
public:
	virtual ~ITextureBuffer(){}

	BufferedTextureType type;
	virtual void setTextureBuffer(const unsigned char* const texture,const int & width, const int & height) = 0;
};