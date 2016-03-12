#pragma once
#include <string>
#include <vector>

//Core includes
#include "Vertex.h"
#include "Texture.h"
#include "Material.h"

//Graphic engine includes
#include "Shader.h"
#include "Context.h"
#include "IRenderer.h"
#include "IRenderable.h"
#include "IVertexArray.h"
#include "OGLTextureBuffer.h"

class Mesh :IRenderable
{
public:
	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	Material material;
	/*  Functions  */
	Mesh(std::vector<Vertex> vertices, std::vector<int> indices, Material material);
	void draw(IRenderer & renderer, Shader shader);
private:
	/*  Render data  */
	shared_ptr<IVertexArray> vertexArray;
	/*  Functions    */
	void setupMesh();
};

