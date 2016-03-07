#pragma once
#include "Texture.h"
#include <vector>
#include <memory>

class TexturesManager
{
	public:

	//Singleton pattern methods
		static TexturesManager& getInstance();
		void operator=(TexturesManager const&) = delete;
		TexturesManager(TexturesManager const&) = delete;
		~TexturesManager();

		vector <shared_ptr<Texture>> texturesBuffers;
		shared_ptr<Texture> CreateTexture(string path, string directory, TextureType type);

	private:
		unique_ptr<unsigned char> TexturesManager::TextureFromFile(const char* path, string directory, int &width, int &height);
		TexturesManager(){};
};

