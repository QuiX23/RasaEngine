#include "Model.h"
#include <iostream>
#include <boost/utility/binary.hpp>
#include <SOIL.h>



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

unique_ptr<unsigned char> Model::TextureFromFile(const char* path, string directory, int &width, int &height)
{
	//Generate texture ID and load texture data 
	string filename = string(path);
	filename = directory + '/' + filename;
	//Dangerous line could in future turn into memory leak!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//SOIL_free_image_data(image);
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	unique_ptr<unsigned char> temp (SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB));
	SOIL_free_image_data(image);
	return move(temp);

}


vector<shared_ptr<Texture>> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<shared_ptr<Texture>> textures;
	for (int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (int j = 0; j < textures_loaded.size(); j++)
		{
			if (textures_loaded[j]->path == str)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{   
			int width = 0, height = 0;
			unique_ptr <unsigned char>tempImage =TextureFromFile(str.C_Str(), this->directory, width, height);
			shared_ptr<Texture> texture = make_shared<Texture>(width, height, typeName,str, &*tempImage);
			textures.push_back(texture);
			this->textures_loaded.push_back(texture);  // Add to loaded textures
		}
	}
	return textures;
}




void Model::draw(IRenderer & renderer, Shader shader)
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
		this->meshes[i].draw(renderer, shader);
}


