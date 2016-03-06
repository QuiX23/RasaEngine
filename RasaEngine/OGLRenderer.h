#pragma once
#include "IRenderer.h"
#include "OGLVertexArray.h"
#include "OGLTextureBuffer.h"


class OGLRenderer:public IRenderer
{

public:
	void renderObject(const IVertexArray & vertexArray, const vector<shared_ptr<ITextureBuffer>> & textureBuffer, Shader shader);
	OGLRenderer();
	~OGLRenderer();

private:


};

