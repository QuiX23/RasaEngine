#pragma once

enum ComponentType
{
	Renderable = 0x0, Light_Source = 0x1
};

class Component
{
public:
	
	ComponentType type;
};