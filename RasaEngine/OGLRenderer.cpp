#include "OGLRenderer.h"

#include <string>

#include <fstream>
#include <sstream>
#include <iostream>
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

void OGLRenderer::render(const Mesh &object)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < object.textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
		// Retrieve texture number (the N in diffuse_textureN)
		stringstream ss;
		string number;
		string name = this->textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();

		glUniform1f(glGetUniformLocation(shader.Program, ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, object.textures[i].id);
	}
	glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);

	// Draw mesh
	glBindVertexArray(object.VAO);
	glDrawElements(GL_TRIANGLES, object.indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


	// Always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < object.textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

OGLRenderer::OGLRenderer()
{
}


OGLRenderer::~OGLRenderer()
{
}

