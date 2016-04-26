#pragma once

#include "IRenderer.h"
#include "Shader.h"

class IRenderable
{
	public:
		Shader shader;
		virtual void draw(IRenderer & renderer) = 0;
};