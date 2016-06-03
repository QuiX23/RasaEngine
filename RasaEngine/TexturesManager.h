#pragma once
#include "Texture2D.h"
#include "vector"
using namespace std;
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
		shared_ptr<Texture> CreateTexture2D(string path, string directory, TextureType type,  float blend, TextureBlendOperation op);
		shared_ptr<Texture> CreateCubeMap(string* filenames);

	private:
		/*  Functions  */
		unique_ptr<unsigned char> TexturesManager::TextureFromFile(string filename, int &width, int &height);
		/*  Singleton pattern methods   */
		TexturesManager(){};
};

