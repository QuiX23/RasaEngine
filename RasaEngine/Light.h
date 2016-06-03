#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "IFrameBuffer.h"

enum class LightType
{
	Directional = 0x0, Point = 0x1, Spot = 0x2
};

class C_Light : public Component
{
public:
	glm::mat4 lightProjection;

	glm::vec3 position;
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	const LightType typeL;
	
	~C_Light();
	C_Light(LightType typeL);

};

