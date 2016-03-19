#pragma once
#include "Light.h"
class Spotlight:public Light
{
public:
	float cutoff;
	glm::vec3 direction;
};

