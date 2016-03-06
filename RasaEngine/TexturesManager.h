#pragma once
#include "Texture.h"
#include "ITextureBuffer.h"
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
		shared_ptr<Texture> CreateTexture(int width, int height, std::string type, aiString path, const unsigned char* const texture);

	private:
		TexturesManager(){};
};

