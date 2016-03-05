#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;



Mesh::Mesh(vector<Vertex> vertices, vector<int> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	this->setupMesh();
}

void Mesh::setupMesh()
{
	vertexArray.setVertexArray(vertices, indices);
	textureSet.setTextureSet(textures);
}

void Mesh::draw(IRenderer & renderer, Shader shader)
{
	renderer.renderObject(vertexArray, textureSet, shader);
	
}

