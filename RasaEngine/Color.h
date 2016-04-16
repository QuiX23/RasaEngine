#pragma once

enum ColorType
{
	ColorType_DIFFUSE, ColorType_SPECULAR, ColorType_AMBIENT
};

struct Color {
	
	float r, g, b, a;
	ColorType type;

	Color(float r, float g, float b, float a, ColorType type)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		this->type = type;
	}

};