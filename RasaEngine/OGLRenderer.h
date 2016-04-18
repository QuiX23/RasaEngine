#pragma once
#include "IRenderer.h"
#include "IVertexArray.h"



class OGLRenderer:public IRenderer
{

public:
	/*  Functions  */
	void renderObject(const IVertexArray & vertexArray, const vector<shared_ptr<Texture>> & textures, Shader shader) override;
	OGLRenderer();
	~OGLRenderer();



};

