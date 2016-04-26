#pragma once
#include <memory>
#include "ITextureBuffer.h"


struct Texture;

class IFrameBuffer
{
public:
	virtual ~IFrameBuffer() {};
	int WIDTH, HIGHT;

	IFrameBuffer(int width, int hight) :WIDTH(width), HIGHT(hight) {};

	virtual std::shared_ptr<ITextureBuffer> getDepthBuffer() = 0;
	virtual std::shared_ptr<ITextureBuffer> getStencilBuffer() = 0;
	virtual std::shared_ptr<ITextureBuffer> getColorBuffer() = 0;
	virtual void setDepthBuffer(bool write) = 0;
	virtual void setDepthStencilBuffer( bool write) = 0;
	virtual void setDepthColorBuffer( bool write) = 0;


};

