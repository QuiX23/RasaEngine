#pragma once

#include "IRenderer.h"

class IRenderable
{
	public:
		virtual void draw(IRenderer & renderer, Shader shader) = 0;
};