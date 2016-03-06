#include "Material.h"



void Material::addTextureToBuffer(shared_ptr<Texture> texturePtr)
{

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

Material::Material()
{

}


Material::~Material()
{
}
