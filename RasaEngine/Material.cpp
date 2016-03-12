#include "Material.h"



void Material::addTextureToBuffer(shared_ptr<Texture> texturePtr)
{
	textures.push_back(texturePtr);
	buffers.push_back(texturePtr->texturBuffer);
}
void Material::temporarySetter()
{
	for (int i = 0; i < textures.size(); i++)
	{
		buffers.push_back(textures[i]->texturBuffer);
	}
}

void addTextureToBuffer(shared_ptr<Texture> texturePtr)
{

}


Material::Material(Shader shader) :shader(shader)
{

}

Material::Material()
{

}

Material::~Material()
{
}
