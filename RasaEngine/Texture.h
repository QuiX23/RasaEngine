#pragma once
#include <assimp\types.h>
#include <memory>

#include "ITextureBuffer.h"

struct Texture {
	int width, height;
	std::string type;
	unique_ptr<unsigned char> image;
	shared_ptr<ITextureBuffer> texturBuffer;
	aiString path;

};