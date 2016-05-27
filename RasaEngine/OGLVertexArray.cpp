#include "OGLVertexArray.h"

void OGLVertexArray::setVertexArray(const vector<Vertex> & vertices, const vector<int> & indices)
{
	
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
		&vertices[0], GL_STATIC_DRAW);

	if (!indices.empty())
	{
		indiciesNum = indices.size();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
			&indices[0], GL_STATIC_DRAW);
	}

	int index = 0;

	// Vertex Positions
	if (vertices[0].Type[VertexFlag_POSITION])
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index++, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));
	}
	// Vertex Normals
	if (vertices[0].Type[VertexFlag_NORMAL])
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index++, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	}
	// Vertex Texture Coords
	if (vertices[0].Type[VertexFlag_TEXCOORDS])
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index++, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
	}
	else if (vertices[0].Type[VertexFlag_COLOR])
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index++, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Color));
	}

	glBindVertexArray(0);
}

OGLVertexArray::OGLVertexArray()
{
}

OGLVertexArray::~OGLVertexArray()
{
}
