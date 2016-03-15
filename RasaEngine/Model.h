#pragma once

#include "IRenderable.h"

#include"assimp\material.h"
#include "Mesh.h"

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
	vector<Mesh> meshes;
	string directory;
	Shader shader;
	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<shared_ptr<Texture>>  loadMaterialTextures(aiMaterial* mat, aiTextureType type);
};

