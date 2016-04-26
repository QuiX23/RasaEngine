#include "TexturesManager.h"
#include <SOIL.h>
#include <algorithm>

TexturesManager& TexturesManager::getInstance()
{
	static TexturesManager  instance; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return instance;
}

unique_ptr<unsigned char> TexturesManager::TextureFromFile(const char* path, string directory, int &width, int &height)
{
	//Generate texture ID and load texture data 
	string filename = string(path);
	filename = directory + '/' + filename;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	unique_ptr<unsigned char> temp(SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB));
	SOIL_free_image_data(image);
	return move(temp);

}
shared_ptr<Texture> TexturesManager::CreateTexture(string path, string directory, TextureType type,  float blend, TextureBlendOperation op)
{

	auto it = find_if(texturesBuffers.begin(), texturesBuffers.end(), [&path](const shared_ptr<Texture>& obj) {return obj->path == path; });

	if (it != texturesBuffers.end())
	{
		// found element. it is an iterator to the first matching element.
		// if you really need the index, you can also get it:
		auto index = std::distance(texturesBuffers.begin(), it);
		return texturesBuffers[index];
	}
	//It's a new texture
	int width = 0, height = 0;
	unique_ptr <unsigned char>tempImage = TextureFromFile(path.c_str(), directory, width, height);
	shared_ptr<Texture> texturePtr = make_shared<Texture>(width, height, type, path, &*tempImage,blend, op);
	texturesBuffers.push_back(texturePtr);
	return texturePtr;

}

TexturesManager::~TexturesManager()
{
}
