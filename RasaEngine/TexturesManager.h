#pragma once
#include "Texture.h"

class TexturesManager
{
	public:

		/*  Singleton pattern methods   */
		static TexturesManager& getInstance();
		void operator=(TexturesManager const&) = delete;
		TexturesManager(TexturesManager const&) = delete;
		~TexturesManager();
		/*  Textures data   */
		vector <shared_ptr<Texture>> texturesBuffers;
		/*  Functions  */
		shared_ptr<Texture> CreateTexture(string path, string directory, TextureType type, unsigned int uv, float blend, TextureBlendOperation op);

	private:
		/*  Functions  */
		unique_ptr<unsigned char> TexturesManager::TextureFromFile(const char* path, string directory, int &width, int &height);
		/*  Singleton pattern methods   */
		TexturesManager(){};
};

