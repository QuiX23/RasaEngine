#pragma once
#include "IRenderer.h"
#include "OGLVertexArray.h"
#include "OGLTextureSet.h"


class OGLRenderer:public IRenderer
{

public:
	void renderObject(const IVertexArray & vertexArray, const ITextureSet & textureSet, Shader shader);
	OGLRenderer();
	~OGLRenderer();

private:


};

