
#include "Context.h"
#include "OGLTextureBuffer.h"
#include "OGLFrameBuffer.h"


OGLFrameBuffer::OGLFrameBuffer(int width, int hight) : IFrameBuffer(width, hight)
{
	glGenFramebuffers(1, &FBO);

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


OGLFrameBuffer::~OGLFrameBuffer()
{
}

std::shared_ptr<ITextureBuffer> OGLFrameBuffer::getDepthBuffer()
{


	return depthBufferTexture;
}

std::shared_ptr<ITextureBuffer> OGLFrameBuffer::getStencilBuffer()
{
	return stencilDepthBufferTexture;
}

std::shared_ptr<ITextureBuffer> OGLFrameBuffer::getColorBuffer()
{
	return colorBufferTexture;
}

void OGLFrameBuffer::setDepthBuffer( bool write)
{
	if (write)
	{
		depthBufferTexture= static_pointer_cast <OGLTextureBuffer>(Context::getInstance().CreateTextureBuffer(nullptr, WIDTH, HIGHT, TextureType_BUFFERDEPTH));

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBufferTexture->id, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void OGLFrameBuffer::setDepthStencilBuffer( bool write)
{
}

void OGLFrameBuffer::setDepthColorBuffer( bool write)
{
}
