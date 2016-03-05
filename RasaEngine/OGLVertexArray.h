#pragma once
#include "IVertexArray.h"

// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class OGLVertexArray :public IVertexArray
{
public:
	GLuint VBO, EBO;

	OGLVertexArray();
	~OGLVertexArray();
	void setVertexArray(const vector<Vertex> & vertices, const vector<int> & indices);
};

