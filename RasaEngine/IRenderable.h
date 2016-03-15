#pragma once

#include "IRenderer.h"
#include "Component.h"

class IRenderable:Component
{
	public:
		virtual void draw(IRenderer & renderer, Shader shader) = 0;
};