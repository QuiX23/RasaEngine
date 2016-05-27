#pragma once


enum ComponentType
{
	ComponentType_RENDERABLE = 0x0, ComponentType_LIGHTS = 0x1, ComponentType_SKYBOX = 0x2, ComponentType_Collider = 0x3, ComponentType_RigidBody = 0x4
};

class Component
{
public:
	

	 const ComponentType type;
	 Component(const Component &temp) :type(temp.type) {};
protected:
	 Component(ComponentType type) :type(type) {};

};