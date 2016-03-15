#pragma once
#include "ITextureBuffer.h"

// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes

class OGLTextureBuffer :public ITextureBuffer
{
public:
	/*  Buffer data  */
	GLuint id;
	/*  Functions  */
	void setTextureBuffer(const unsigned char* const texture, const int & width, const int & height);
	OGLTextureBuffer();
	~OGLTextureBuffer();

};

