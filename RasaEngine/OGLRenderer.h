#pragma once
#include "IRenderer.h"
#include "IVertexArray.h"
#include "ITextureBuffer.h"


class OGLRenderer:public IRenderer
{

public:
	void renderObject(const IVertexArray & vertexArray, const vector<shared_ptr<ITextureBuffer>> & textureBuffer, Shader shader);
	OGLRenderer();
	~OGLRenderer();

private:


};

