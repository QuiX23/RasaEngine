#include "OGLRenderer.h"

#include <string>
#include <fstream>
#include <sstream>

#include "OGLVertexArray.h"
#include "OGLTextureBuffer.h"

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
		
		string name;
		switch (tBuffer.type)
		{
		case BufferedTextureType_DIFFUSE:
			name = "texture_diffuse"+to_string(diffuseNr++);
			break;
		case BufferedTextureType_SPECULAR:
			name = "texture_specular"+to_string(specularNr++);
			break;
		}

		glUniform1f(glGetUniformLocation(shader.Program, ("material." + name).c_str()), i);
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
