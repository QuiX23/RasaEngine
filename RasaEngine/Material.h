#pragma once
#include <string>
#include <vector>
#include <memory>
//Core includes
#include "Texture.h"

//Graphic engine includes
#include "ITextureBuffer.h"
#include "Shader.h"

class Material
{
	public:
	std::vector<shared_ptr<Texture>> textures;
	std::vector <shared_ptr<ITextureBuffer>> buffers;

	void addTexture(shared_ptr<Texture> texturePtr);
	void temporarySetter();
	//Shader shader;
	
	Material();
	~Material();

	private:
	void addTextureToBuffer(shared_ptr<Texture> texturePtr);
	
};

