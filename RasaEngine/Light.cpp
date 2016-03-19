#include "Light.h"


Light::Light(LightType type) :type(type)
{
}

Light::Light() : type(LightType::Directional)
{
}


Light::~Light()
{
}
