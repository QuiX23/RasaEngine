#include "Mesh.h"

#include "Context.h"




Mesh::Mesh(vector<Vertex> vertices, vector<int> indices, Material material, Shader shader) :vertices(vertices), indices(indices), material (material)
{
	this->shader = shader;
	this->setupMesh();
}

void Mesh::setupMesh()
{
	vertexArray = Context::getInstance().CreateVertexArray(vertices, indices);
}

void Mesh::draw(IRenderer & renderer)
{
	if (!shader.initialized) throw exception("Renderable don't have any shader atached!");
	renderer.renderObject(*vertexArray, material.buffers, shader);

}

