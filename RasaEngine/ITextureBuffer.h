#pragma once

enum TextureType;

class ITextureBuffer
{
public:
	virtual ~ITextureBuffer(){}

	virtual void setTextureBuffer(const unsigned char* const texture,const int & width, const int & height,TextureType type) = 0;
};
