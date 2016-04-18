#include "Material.h"

void Material::addTexture(shared_ptr<Texture> texturePtr)
{
	textures.push_back(texturePtr);
}

void Material::addColor(shared_ptr<Color> colorPtr)
{
	colors.push_back(colorPtr);
}

Material::Material()
{

}

Material::~Material()
{
}
