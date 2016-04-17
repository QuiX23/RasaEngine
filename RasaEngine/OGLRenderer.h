#pragma once
#include "IRenderer.h"
#include "IVertexArray.h"
#include "ITextureBuffer.h"


class OGLRenderer:public IRenderer
{

public:
	/*  Functions  */
	void renderObject(const IVertexArray & vertexArray, const vector<shared_ptr<ITextureBuffer>> & textureBuffer, Shader shader) override;
	OGLRenderer();
	~OGLRenderer();

private:


};

