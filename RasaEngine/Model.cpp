#include "Model.h"

#include <iostream>
#include <boost/utility/binary.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "TexturesManager.h"
#include "Component.h"


/*  Functions   */
Model::Model(char* path, Shader shader): Component(ComponentType_RENDERABLE)
{
	this->shader = shader;
	this->loadModel(path);
}

Model Model::genericPlane()
{
	vector<Mesh> m = { Mesh::genericPlane() };
	return Model(m);
}

Model::Model(vector<Mesh> meshes) : Component(ComponentType_RENDERABLE)
{
	this->meshes = meshes;
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
		vertex.Type = BOOST_BINARY(0011);

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
			vertex.Type[VertexFlag_TEXCOORDS] = 1;
		}
		
		for (int j(0); j < AI_MAX_NUMBER_OF_COLOR_SETS; j++)
			if (mesh->HasVertexColors(j))
			{
				glm::vec4 vec;
				vec.r = mesh->mColors[j][i].r;
				vec.g = mesh->mColors[j][i].g;
				vec.b = mesh->mColors[j][i].b;
				vec.a = mesh->mColors[j][i].a;
				vertex.Color = vec;
				vertex.Type[VertexFlag_COLOR] = 1;
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
		this->loadMaterialColors(aMaterial, &material);
		this->loadMaterialTextures(aMaterial, &material);
	}

	return Mesh(vertices, indices, material, shader);
}

void Model::loadMaterialTextures(aiMaterial* aiMat, Material* mat)
{
	aiString aStr;
	unsigned int uv = 0;
	float blend = 0.f;
	aiTextureOp op = aiTextureOp_SmoothAdd;

	for (int i = 0; i < aiMat->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiMat->GetTexture(aiTextureType_DIFFUSE, i, &aStr, NULL, &uv, &blend, &op, NULL);
		string str(aStr.C_Str());
		cout << str << ": ";
		if (uv != NULL)
			cout << "uv: " + to_string(uv);
		if (blend != NULL)
			cout << " blend: " + to_string(blend);
		if (op != NULL)
			cout << " op: " + to_string(op);
		cout<< endl;

		shared_ptr<Texture> texture = TexturesManager::getInstance().CreateTexture2D(str, this->directory, (TextureType)aiTextureType_DIFFUSE,  blend, (TextureBlendOperation) op);
		mat->addTexture(texture);
	}

	for (int i = 0; i < aiMat->GetTextureCount(aiTextureType_SPECULAR); i++)
	{
		aiMat->GetTexture(aiTextureType_SPECULAR, i, &aStr);
		string str(aStr.C_Str());
		shared_ptr<Texture> texture = TexturesManager::getInstance().CreateTexture2D(str, this->directory, (TextureType)aiTextureType_SPECULAR,  blend, (TextureBlendOperation)op);
		mat->addTexture(texture);
	}
}

void Model::loadMaterialColors(aiMaterial* aiMat, Material* mat)
{
	aiColor4D aColor(0.f,0.f,0.f,0.f);
	aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_DIFFUSE, &aColor);
	if(!aColor.IsBlack())
	{
		shared_ptr<Color> color = make_shared<Color>(aColor.r, aColor.g, aColor.b, aColor.a, ColorType_DIFFUSE);
		mat->addColor(color);
		cout << "Base color: " << color->r << "," << color->g << "," << color->b << endl;
	}

	aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_SPECULAR, &aColor);
	if(!aColor.IsBlack())
	{
		shared_ptr<Color> color = make_shared<Color>(aColor.r, aColor.g, aColor.b, aColor.a, ColorType_SPECULAR);
		mat->addColor(color);
	}
	aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_AMBIENT, &aColor);
	if (!aColor.IsBlack())
	{
		shared_ptr<Color> color = make_shared<Color>(aColor.r, aColor.g, aColor.b, aColor.a, ColorType_AMBIENT);
		mat->addColor(color);
	}
}

void Model::draw(IRenderer & renderer)
{
	//if (!shader.initialized) throw exception("Renderable don't have any shader atached!");
	
	for (GLuint i = 0; i < this->meshes.size(); i++)
    {
		this->meshes[i].draw(renderer);
	}
}