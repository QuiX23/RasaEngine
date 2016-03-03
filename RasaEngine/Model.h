#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "IRenderable.h"

class Mesh;

class Model :public IRenderable
{
public:
	/*  Functions   */
	Model(GLchar* path);
	void draw(IRenderer & renderer);
private:
	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::vector<Mesh::Texture> textures_loaded;
	std::string directory;
	/*  Functions   */
	void loadModel(std::string path);
	GLint TextureFromFile(const char* path, std::string directory);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Mesh::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
};

