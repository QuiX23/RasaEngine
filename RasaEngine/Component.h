#pragma once


enum ComponentType
{
	Renderable = 0x0, Lights = 0x1,
};

class Component
{
public:
	

	 const ComponentType type;
	 Component(const Component &temp) :type(temp.type) {};
protected:
	 Component(ComponentType type) :type(type) {};

};