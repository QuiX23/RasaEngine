#include "TexturesManager.h"


TexturesManager& TexturesManager::getInstance()
{
	static TexturesManager  instance; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return instance;
}
shared_ptr<Texture> TexturesManager::CreateTexture(int width, int height, std::string type, aiString path, const unsigned char* const texture)
{

	auto it = find_if(texturesBuffers.begin(), texturesBuffers.end(), [&path](const shared_ptr<Texture>& obj) {return obj->path == path; });

	if (it != texturesBuffers.end())
	{
		// found element. it is an iterator to the first matching element.
		// if you really need the index, you can also get it:
		auto index = std::distance(texturesBuffers.begin(), it);
		return texturesBuffers[index];
	}
	shared_ptr<Texture> texturePtr = make_shared<Texture>(width, height, type, path, texture);
	texturesBuffers.push_back(texturePtr);
	return texturePtr;

}

TexturesManager::~TexturesManager()
{
}
