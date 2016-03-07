#pragma once
#include <memory>

#include "ITextureBuffer.h"
#include "Context.h"

enum TextureType
{
	TextureType_NONE = 0x0, TextureType_DIFFUSE = 0x1, TextureType_SPECULAR = 0x2, TextureType_AMBIENT = 0x3,
	TextureType_EMISSIVE = 0x4, TextureType_HEIGHT = 0x5, TextureType_NORMALS = 0x6, TextureType_SHININESS = 0x7,
	TextureType_OPACITY = 0x8, TextureType_DISPLACEMENT = 0x9, TextureType_LIGHTMAP = 0xA, TextureType_REFLECTION = 0xB,
	TextureType_UNKNOWN = 0xC
};

struct Texture {
	int width, height;
	TextureType type;
	shared_ptr<ITextureBuffer> texturBuffer;
	string path;

	Texture(int width, int height, TextureType type, string path, const unsigned char* const texture)
	{
		this->width = width;
		this->height = height;
		this->type = type;
		this->path = path;
		this->texturBuffer = Context::getInstance().CreateTextureBuffer(texture, width, height);
	}

};

