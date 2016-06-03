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
	renderer.renderObject(*vertexArray, material.textures, shader);

}

Mesh Mesh::genericPlane()
{
	Shader shader("GenericShader.vert", "GenericShader.frag");
	
	vector<Vertex> vertices;
	
	vector<int> indices= { 0, 1, 2, 2, 3, 1 };

		GLfloat planeVertices[] = {
		// Positions          
		-1.0f,  0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		-1.0f, 0.0f, -1.0f,
		1.0f, 0.0f, -1.0f,

	};

	for (int i = 0; i < 4; i++)
	{
		Vertex vertex;
		vertex.Type[VertexFlag_POSITION] = 1;
		vertex.Type[VertexFlag_COLOR] = 1;
		vertex.Type[VertexFlag_NORMAL] = 1;
		
		glm::vec3 vector;
		auto color = glm::vec4(255, 255, 255, 255);
		auto normal = glm::vec3(0,1,0);

		vector.x = planeVertices[i*3];
		vector.y = planeVertices[i*3+1];
		vector.z = planeVertices[i*3+2];
		
		vertex.Position = vector;
		vertex.Color = color;
		vertex.Normal = normal;
		
		vertices.push_back(vertex);
	}

	auto material=Material ();

	auto mesh = Mesh(vertices, indices, material, shader);

	return mesh;
}
