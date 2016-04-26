#pragma once
#include "IRenderer.h"
#include "OGLTextureBuffer.h"


class OGLRenderer:public IRenderer
{

public:
	/*  Functions  */
	void renderObject(const IVertexArray & vertexArray, const vector<shared_ptr<Texture>> & textures, Shader shader) override;
	void unSetFrameBuffer() override;
	void setFrameBuffer(const IFrameBuffer& frameBuffer) override;
	void setShadowMap(const ITextureBuffer& shadowMap) override;
	OGLRenderer();
	~OGLRenderer();
private:
	OGLTextureBuffer shadowMap;


};

