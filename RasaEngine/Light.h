#pragma once
#include "Component.h"
#include <glm/glm.hpp>

enum LightType
{
	Directional = 0x0, Point = 0x1, Area=0x2
};

class Light : Component
{
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;



public:
	LightType type;
	Light(LightType type);
	Light();
	~Light();
};

