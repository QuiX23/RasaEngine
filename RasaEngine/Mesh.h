#pragma once
#include <string>
#include <vector>
#include "Shader.h"
#include <assimp\types.h>
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "IRenderable.h"

class Mesh : public IRenderable
{
public:
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct Texture {
		GLuint id;
		std::string type;
		aiString path;
	};
	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	/*  Functions  */
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void draw(IRenderer & renderer);
private:
	/*  Render data  */
	GLuint VAO, VBO, EBO;
	/*  Functions    */
	void setupMesh();
};

