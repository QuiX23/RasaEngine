#pragma once

//Core includes
#include "Vertex.h"
#include "Material.h"

//Graphic engine includes
#include "Shader.h"
#include "IRenderer.h"
#include "IRenderable.h"
#include "IVertexArray.h"

class Mesh :IRenderable
{
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<int> indices;
	Material material;
	/*  Functions  */
	Mesh(vector<Vertex> vertices, vector<int> indices, Material material, Shader shader);
	static Mesh genericPlane();
	void draw(IRenderer & renderer) override;
private:
	/*  Render data  */
	shared_ptr<IVertexArray> vertexArray;
	/*  Functions    */
	void setupMesh();
};

