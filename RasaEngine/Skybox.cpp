#include "Skybox.h"
#include "TexturesManager.h"
#include "Context.h"

Skybox::Skybox(string* paths, Shader shader) : Component(ComponentType_SKYBOX)
{
	this->shader = shader;
	this->loadSkybox(paths);
}

void Skybox::loadSkybox(string* paths)
{
	this->vertexArray = Context::getInstance().CreateSkyBoxVertexArray();
	this->textures.push_back(TexturesManager::getInstance().CreateCubeMap(paths));
}

void Skybox::draw(IRenderer& renderer)
{
	if (!shader.initialized) throw exception("Renderable don't have any shader atached!");
	renderer.renderObject(*vertexArray, textures, shader);
}

