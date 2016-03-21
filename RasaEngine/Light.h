#pragma once
#include "Component.h"
#include <glm/glm.hpp>

enum class LightType
{
	Directional = 0x0, Point = 0x1, Spot = 0x2
};

class C_Light : public Component
{
public:
	glm::vec3 position;
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	const LightType typeL;
	
	~C_Light();
//protected:
	C_Light(LightType typeL);

};

