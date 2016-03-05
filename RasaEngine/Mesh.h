#pragma once
#include <string>
#include <vector>
#include "Shader.h"

#include "Context.h"
#include "IRenderer.h"
#include "IRenderable.h"

#include "Vertex.h"
#include "Texture.h"

#include "Context.h"
#include "IVertexArray.h"
#include "OGLTextureSet.h"

class Mesh :IRenderable
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
	/*  Render data  */
	shared_ptr<IVertexArray> vertexArray;
	OGLTextureSet textureSet;
	/*  Functions    */
	void setupMesh();
};

