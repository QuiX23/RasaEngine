#pragma once

#include "IRenderable.h"

#include "Mesh.h"
#include"assimp\material.h"

class Mesh;
class aiNode;
class aiMesh;
class aiScene;
class aiMaterial;

class Model:public IRenderable
{
public:
	/*  Functions   */
	Model(char* path);
	Model(char* path, Shader shader);
	
	void draw(IRenderer & renderer);
	void draw(IRenderer & renderer, Shader shader);
private:
	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;
	Shader modelShader;
	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<shared_ptr<Texture>>  loadMaterialTextures(aiMaterial* mat, aiTextureType type);
};

