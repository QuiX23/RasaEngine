#include "Skybox.h"
#include "TexturesManager.h"
#include "Context.h"

Skybox::Skybox(string* paths, Shader shader) : Component(ComponentType_SKYBOX)
{
	this->shader = shader;
	this->loadSkybox(paths);
}

void Skybox::loadSkybox(string* paths)
{
	this->textures.push_back(TexturesManager::getInstance().CreateCubeMap(paths));
	generateVertexArray();
}

void Skybox::draw(IRenderer& renderer)
{
	if (!shader.initialized) throw exception("Renderable don't have any shader atached!");
	renderer.renderObject(*vertexArray, textures, shader);
}

void Skybox::generateVertexArray()
{
	GLfloat skyboxVertices[] = {
		// Positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	vector<Vertex> vertices;

	for (int i = 0; i < 36; i++)
	{
		Vertex vertex;
		vertex.Type[VertexFlag_POSITION] = 1;

		glm::vec3 vector;

		vector.x = skyboxVertices[3*i];
		vector.y = skyboxVertices[3*i + 1];
		vector.z = skyboxVertices[3*i + 2];
		vertex.Position = vector;
		vertices.push_back(vertex);
	}
	vertexArray = Context::getInstance().CreateVertexArray(vertices, vector<int>());
}