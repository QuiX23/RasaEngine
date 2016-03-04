#pragma once
#include "Texture.h"
#include <vector>
using namespace std;

class ITextureSet
{
public:
	std::vector<Texture> textures;
	virtual void setTextureSet(const vector<Texture> & textures) = 0;
};