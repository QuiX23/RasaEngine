#pragma once
#include "IVertexArray.h"

// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes

class OGLVertexArray :public IVertexArray
{
public:
	GLuint VAO, VBO, EBO, indiciesNum;

	OGLVertexArray();
	~OGLVertexArray();
	void setVertexArray(const vector<Vertex> & vertices, const vector<int> & indices);
};

