#pragma once

#include "Mesh.h"

class IRenderer
{
public:
	virtual void render(const Mesh & object) = 0;
};