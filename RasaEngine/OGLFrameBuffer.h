#pragma once
#include "IFrameBuffer.h"
#include "../packages/glew.v140.1.12.0/build/native/include/GL/glew.h"
#include "ITextureBuffer.h"
#include "OGLTextureBuffer.h"


class OGLFrameBuffer :
	public IFrameBuffer
{
public:
	 OGLFrameBuffer(int width, int hight);
	 ~OGLFrameBuffer();

	 GLuint FBO;

	 std::shared_ptr<ITextureBuffer> getDepthBuffer()override;
	 std::shared_ptr<ITextureBuffer> getStencilBuffer() override;
	 std::shared_ptr<ITextureBuffer> getColorBuffer() override;
	 void setDepthBuffer( bool write) override;
	 void setDepthStencilBuffer(bool write)override;
	 void setDepthColorBuffer(bool write) override;
private:
	std::shared_ptr<OGLTextureBuffer> depthBufferTexture;
	std::shared_ptr<OGLTextureBuffer> stencilDepthBufferTexture;
	std::shared_ptr<OGLTextureBuffer> colorBufferTexture;
};

