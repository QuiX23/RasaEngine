#pragma once
#include "Light.h"
class Pointlight : public C_Light
{
public:
	float constant = 1.0f, linear = 0.14f, quadratic = 0.07f;
};

