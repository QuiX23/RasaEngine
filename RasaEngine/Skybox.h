#pragma once

#include "IRenderable.h"
#include "Component.h"

#include "Texture.h"

class Skybox :public IRenderable,public Component
{
public:
	Skybox(string* paths, Shader shader);
	void draw(IRenderer & renderer);

private:
	vector<shared_ptr<Texture>> textures;
	shared_ptr<IVertexArray> vertexArray;

	void loadSkybox(string* paths);
};