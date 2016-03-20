#pragma once

#include "IRenderer.h"
#include "Component.h"

class IRenderable
{
	public:
		Shader shader;
		virtual void draw(IRenderer & renderer) = 0;
};