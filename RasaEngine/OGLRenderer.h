#pragma once
#include "IRenderer.h"


class OGLRenderer:public IRenderer
{
public:
	void render(const Mesh & object);
	OGLRenderer();
	~OGLRenderer();
};

