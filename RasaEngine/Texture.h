#pragma once
#include <memory>

#include "ITextureBuffer.h"
#include "Context.h"

struct Texture {
	int width, height;
	std::string type;
	shared_ptr<ITextureBuffer> texturBuffer;
	string path;

	Texture(int width, int height, std::string type, string path, const unsigned char* const texture)
	{
		this->width = width;
		this->height = height;
		this->type = type;
		this->path = path;
		this->texturBuffer = Context::getInstance().CreateTextureBuffer(texture, width, height);
	}

};