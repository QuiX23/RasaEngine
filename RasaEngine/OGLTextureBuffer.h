#pragma once
#include "ITextureBuffer.h"

// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes

class OGLTextureBuffer :public ITextureBuffer
{
public:
	GLuint id;
	void setTextureBuffer(const unsigned char* const texture, const int & width, const int & height);
	OGLTextureBuffer();
	~OGLTextureBuffer();
};

