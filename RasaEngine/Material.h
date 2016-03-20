#pragma once

//Core includes
#include "Texture.h"

//Graphic engine includes
#include "ITextureBuffer.h"
#include "Shader.h"


class Material
{
	public:
	/*  Material data  */
	vector<shared_ptr<Texture>> textures;
	vector <shared_ptr<ITextureBuffer>> buffers;
	/*  Functions  */
	void addTexture(shared_ptr<Texture> texturePtr);
	void temporarySetter();
	
	Material();
	Material(Shader shader);
	~Material();

	private:
	
	void addTextureToBuffer(shared_ptr<Texture> texturePtr);
	
};

