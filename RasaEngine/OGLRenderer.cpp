#include "OGLRenderer.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;




void OGLRenderer::renderObject(const IVertexArray & vertexArray, const vector<shared_ptr<ITextureBuffer>> & textureBuffer, Shader shader)
{
	const OGLVertexArray &vArray = static_cast <const OGLVertexArray&>(vertexArray);
	//OGLVertexArray &vArray = dynamic_cast < OGLVertexArray&>(const_cast < IVertexArray&>(vertexArray));
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < textureBuffer.size(); i++)
	{
		const OGLTextureBuffer &tBuffer = static_cast <const OGLTextureBuffer&>(*textureBuffer[i]);
		glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
		// Retrieve texture number (the N in diffuse_textureN)
		stringstream ss;
		string number;
		//string name = tBuffer.type;
		string name = "texture_diffuse";
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();

		glUniform1f(glGetUniformLocation(shader.Program, ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, tBuffer.id);
	}
	glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);

	glBindVertexArray(vArray.VAO);
	glDrawElements(GL_TRIANGLES, vArray.indiciesNum, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


	// Always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < textureBuffer.size(); i++)
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

