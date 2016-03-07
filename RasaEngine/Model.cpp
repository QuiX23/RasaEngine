#include "Model.h"
#include <iostream>
#include <boost/utility/binary.hpp>
#include <SOIL.h>
#include "TexturesManager.h"



using namespace std;

/*  Functions   */
Model::Model(GLchar* path)
{
	this->loadModel(path);
}

void Model::loadModel(std::string path){

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}
	this->directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<int> indices;
	Material material;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.Type = BOOST_BINARY(111);

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;


		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* aMaterial = scene->mMaterials[mesh->mMaterialIndex];
		vector<shared_ptr<Texture>> diffuseMaps = this->loadMaterialTextures(aMaterial,
			aiTextureType_DIFFUSE, "texture_diffuse");
		material.textures.insert(material.textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<shared_ptr<Texture>> specularMaps = this->loadMaterialTextures(aMaterial,
			aiTextureType_SPECULAR, "texture_specular");
		material.textures.insert(material.textures.end(), specularMaps.begin(), specularMaps.end());
	}
	material.temporarySetter();

	return Mesh(vertices, indices, material);
}

vector<shared_ptr<Texture>> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<shared_ptr<Texture>> textures;
	for (int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString aStr;
		mat->GetTexture(type, i, &aStr);
		string str(aStr.C_Str());
		shared_ptr<Texture> texture = TexturesManager::getInstance().CreateTexture(str, this->directory, typeName);
		textures.push_back(texture);
		
	}
	return textures;
}




void Model::draw(IRenderer & renderer, Shader shader)
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
		this->meshes[i].draw(renderer, shader);
}


