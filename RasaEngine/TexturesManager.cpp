#include "TexturesManager.h"
#include <SOIL.h>
#include <algorithm>

TexturesManager& TexturesManager::getInstance()
{
	static TexturesManager  instance; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return instance;
}

unique_ptr<unsigned char> TexturesManager::TextureFromFile(string filename, int &width, int &height)
{
	//Generate texture ID and load texture data 
	//unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	unique_ptr<unsigned char> temp(SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB));
	//SOIL_free_image_data(image);
	return move(temp);
}
shared_ptr<Texture> TexturesManager::CreateTexture2D(string path, string directory, TextureType type, float blend, TextureBlendOperation op)
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
	string filename = directory + '/' + string(path);

	unique_ptr<unsigned char> tempImage = TextureFromFile(filename, width, height);
	shared_ptr<Texture> texturePtr = make_shared<Texture2D>(width, height, type, path, &*tempImage, blend, op);
	texturesBuffers.push_back(texturePtr);
	return texturePtr;
}

shared_ptr<Texture> TexturesManager::CreateCubeMap(string* filenames)
{
	int widths[6], heights[6];
	vector<const unsigned char*> tempImages;
	for (int i = 0; i < 6; i++)
	{
		//Rozwiazanie tymczasowe

		/*unique_ptr<unsigned char> tempImage = TextureFromFile(filenames[i], widths[i], heights[i]);
		tempImages.push_back(&*tempImage);*/
		unsigned char* image = SOIL_load_image(filenames[i].c_str(), &widths[i], &heights[i], 0, SOIL_LOAD_RGB);
		tempImages.push_back(image);
	}
	shared_ptr<Texture> texturePtr = make_shared<CubeMap>(filenames[0], widths, heights, tempImages);
	texturesBuffers.push_back(texturePtr);
	return texturePtr;
}

TexturesManager::~TexturesManager()
{
}
