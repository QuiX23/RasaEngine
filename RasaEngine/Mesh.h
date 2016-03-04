#pragma once
#include <string>
#include <vector>
#include "Shader.h"


#include "IRenderer.h"
#include "IRenderable.h"

#include "Vertex.h"
#include "Texture.h"

#include "OGLVertexArray.h"
#include "OGLTextureSet.h"

class Mesh:IRenderable
{
public:

	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	std::vector<Texture> textures;
	/*  Functions  */
	Mesh(std::vector<Vertex> vertices, std::vector<int> indices, std::vector<Texture> textures);
	void draw(IRenderer & renderer, Shader shader);
private:
	OGLVertexArray vertexArray;
	OGLTextureSet textureSet;
	/*  Render data  */
	/*  Functions    */
	void setupMesh();
};

