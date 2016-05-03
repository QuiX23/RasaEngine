#include "OGLRenderer.h"

#include <string>

#include "OGLVertexArray.h"
#include "OGLTextureBuffer.h"
#include "Context.h"
#include "Shader.h"
#include "IFrameBuffer.h"
#include "OGLFrameBuffer.h"

using namespace std;





void OGLRenderer::renderObject(const IVertexArray & vertexArray, const vector<shared_ptr<Texture>> & textures, Shader shader)
{


	const OGLVertexArray &vArray = static_cast <const OGLVertexArray&>(vertexArray);
	//OGLVertexArray &vArray = dynamic_cast < OGLVertexArray&>(const_cast < IVertexArray&>(vertexArray));
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;

	

	for (GLuint i = 0; i < textures.size(); i++)
	{
		const OGLTextureBuffer &tBuffer = static_cast <const OGLTextureBuffer&>(*textures[i]->texturBuffer);
		glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
		// Retrieve texture number (the N in diffuse_textureN)
		string name;
		switch (textures[i]->type)
		{
		case TextureType_DIFFUSE:
			name = "texture_diffuse"+to_string(diffuseNr++);
			break;
		case TextureType_SPECULAR:
			name = "texture_specular"+to_string(specularNr++);
			break;
		}

		glUniform1f(glGetUniformLocation(shader.Program, ("material." + name).c_str()), i );
		glBindTexture(GL_TEXTURE_2D, tBuffer.id);
	}

	glActiveTexture(GL_TEXTURE0 + textures.size());
	glUniform1i(glGetUniformLocation(shader.Program, "shadowMap"), textures.size());
	glBindTexture(GL_TEXTURE_2D, shadowMap.id);

	glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);

	glBindVertexArray(vArray.VAO);
	glDrawElements(GL_TRIANGLES, vArray.indiciesNum, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	

	// Always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	glActiveTexture(GL_TEXTURE0+ textures.size());
	glBindTexture(GL_TEXTURE_2D, textures.size());

	
}


 void OGLRenderer::unSetFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Context::getInstance().screenWidth, Context::getInstance().screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

void OGLRenderer::setFrameBuffer(const IFrameBuffer & frameBuffer) 
{
		glViewport(0, 0, frameBuffer.WIDTH, frameBuffer.HIGHT);
		OGLFrameBuffer fb = static_cast <const OGLFrameBuffer&>(frameBuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, fb.FBO);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
}

 void OGLRenderer::setShadowMap(const ITextureBuffer & sMap)
{
	shadowMap = static_cast <const OGLTextureBuffer&>(sMap);
}

OGLRenderer::OGLRenderer(): shadowMap()
{


	// Define the viewport dimensions
	glViewport(0, 0, Context::getInstance().screenWidth, Context::getInstance().screenHeight);

	// Setup some OpenGL options
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
}

OGLRenderer::~OGLRenderer()
{
}
