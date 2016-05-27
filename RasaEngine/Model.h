#pragma once

#include "IRenderable.h"

#include"assimp\material.h"
#include "Mesh.h"
#include "Component.h"

class Mesh;
class aiNode;
class aiMesh;
class aiScene;
class aiMaterial;

class Model:public IRenderable,public Component
{
public:
	/*  Functions   */
	Model(char* path, Shader shader);
	static Model genericPlane();
	void draw(IRenderer & renderer);
private:
	Model(vector<Mesh> meshes);
	/*  Model Data  */
	vector<Mesh> meshes;
	string directory;
	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	void loadMaterialColors(aiMaterial* aiMat, Material* mat);
	void loadMaterialTextures(aiMaterial* aiMat, Material* mat);
};