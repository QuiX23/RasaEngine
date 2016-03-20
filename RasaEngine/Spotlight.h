#pragma once
#include "Light.h"
class Spotlight:public C_Light
{
public:
	float cutoff;
	glm::vec3 direction;
};

