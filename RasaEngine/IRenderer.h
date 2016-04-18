#pragma once
#include <memory>

#include "Shader.h"
#include "IVertexArray.h"
#include "Texture.h"

class IRenderer
{
public:
	virtual ~IRenderer(){}

	virtual void renderObject(const IVertexArray & vertexArray, const vector<shared_ptr<Texture>> & textures, Shader shader) = 0;
};