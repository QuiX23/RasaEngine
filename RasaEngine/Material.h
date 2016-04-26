#pragma once

//Core includes
#include "Texture.h"
#include "Color.h"

//Graphic engine includes
#include "Shader.h"
#include <vector>

using namespace std;

class Material
{
	public:
	/*  Material data  */
	vector<shared_ptr<Texture>> textures;
	vector<shared_ptr<Color>> colors;
	
	/*  Functions  */
	void addTexture(shared_ptr<Texture> texturePtr);
	void addColor(shared_ptr<Color> colorPtr);
	
	Material();
	Material(Shader shader);
	~Material();

};

