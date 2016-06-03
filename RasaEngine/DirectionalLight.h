#pragma once
#include "Light.h"
class DirectionalLight : public C_Light
{
public:
	DirectionalLight();
	glm::vec3 direction;
};

