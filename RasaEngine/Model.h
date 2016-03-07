#pragma once



#include "IRenderable.h"

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh;

class Model:public IRenderable
{
public:
	/*  Functions   */
	Model(GLchar* path);
	void draw(IRenderer & renderer, Shader shader);
private:
	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;
	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<shared_ptr<Texture>>  loadMaterialTextures(aiMaterial* mat, aiTextureType type);
};

