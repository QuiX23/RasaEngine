#include "Mesh.h"

#include "Context.h"




Mesh::Mesh(vector<Vertex> vertices, vector<int> indices, Material material) :vertices(vertices), indices(indices), material (material)
{
	this->setupMesh();
}

void Mesh::setupMesh()
{
	vertexArray = Context::getInstance().CreateVertexArray(vertices, indices);
}

void Mesh::draw(IRenderer & renderer, Shader shader)
{
	if (material.shader.initialized) shader = material.shader;
	renderer.renderObject(*vertexArray, material.buffers, shader);

}

