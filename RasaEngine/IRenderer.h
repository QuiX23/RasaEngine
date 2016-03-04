#pragma once

#include "Shader.h"
#include "IVertexArray.h"
#include "ITextureSet.h"

class IRenderer
{
public:
	virtual void renderObject(const IVertexArray & vertexArray, const ITextureSet & textureSet, Shader shader) = 0;
};