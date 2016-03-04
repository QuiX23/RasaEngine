#pragma once
#include "ITextureSet.h"

using namespace std;

class OGLTextureSet:public ITextureSet
{
public:

	void setTextureSet(const vector<Texture> & textures);
	OGLTextureSet();
	~OGLTextureSet();
};

