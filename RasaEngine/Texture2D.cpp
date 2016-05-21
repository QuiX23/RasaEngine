#include "Texture2D.h"
#include "Context.h"

Texture2D::Texture2D(int width, int height, TextureType type, string path, const unsigned char* const texture, float blend, TextureBlendOperation op)
{
	this->width = width;
	this->height = height;
	this->type = type;
	this->path = path;
	this->textureBuffer = Context::getInstance().CreateTextureBuffer(texture, width, height, type);
	this->blend = blend;
	this->op = op;
}