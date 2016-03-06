#pragma once
#include <assimp\types.h>
#include <memory>

#include "ITextureBuffer.h"
#include "Context.h"

struct Texture {
	int width, height;
	std::string type;
	shared_ptr<ITextureBuffer> texturBuffer;
	aiString path;

	Texture(int width, int height, std::string type, aiString path, const unsigned char* const texture)
	{
		this->width = width;
		this->height = height;
		this->type = type;
		this->path = path;
		this->texturBuffer = Context::getInstance().CreateTextureBuffer(texture, width, height);
	}

};