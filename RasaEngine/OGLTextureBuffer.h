#pragma once
#include "ITextureBuffer.h"

// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes

enum TextureType;

class OGLTextureBuffer :public ITextureBuffer
{
public:
	/*  Buffer data  */
	GLuint id;
	/*  Functions  */
	void setTextureBuffer(const unsigned char* const texture, const int& width, const int& height, TextureType type) override;
	void setCubeMapBuffer(std::vector<const unsigned char*>& textures, const int* widths, const int* heights) override;
	OGLTextureBuffer();
	~OGLTextureBuffer();

};

