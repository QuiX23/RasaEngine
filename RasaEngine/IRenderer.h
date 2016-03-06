#pragma once
#include <memory>

#include "Shader.h"
#include "IVertexArray.h"
#include "ITextureBuffer.h"

class IRenderer
{
public:
	virtual void renderObject(const IVertexArray & vertexArray, const vector<shared_ptr<ITextureBuffer>> & textureBuffer, Shader shader) = 0;
};