#pragma once
#include <memory>

enum ComponentType
{
	TextureType_NONE = 0x0, TextureType_DIFFUSE = 0x1
};

class Component
{
public:
	
	ComponentType type;
};