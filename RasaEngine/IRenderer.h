#pragma once
#include <memory>
#include "Texture.h"
#include <vector>

using namespace std;

class IFrameBuffer;
class  IVertexArray;
class Shader;

class IRenderer
{
public:
	virtual ~IRenderer(){}

	virtual void renderObject(const IVertexArray & vertexArray, const vector<shared_ptr<Texture>> & textures, Shader shader) = 0;
	virtual void setFrameBuffer(const IFrameBuffer & frameBuffer)=0;
	virtual void setShadowMap(const ITextureBuffer & sMap) = 0;
	virtual void unSetFrameBuffer() = 0;
};
