#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;



Mesh::Mesh(vector<Vertex> vertices, vector<int> indices, Material material)
{
	this->vertices = vertices;
	this->indices = indices;
	this->material = material;

	this->setupMesh();
}

void Mesh::setupMesh()
{
	vertexArray = Context::getInstance().CreateVertexArray(vertices, indices);
}

void Mesh::draw(IRenderer & renderer, Shader shader)
{
	int a = 0;
	renderer.renderObject(*vertexArray, material.buffers, shader);

}

