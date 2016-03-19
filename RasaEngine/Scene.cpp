#include "Scene.h"

shared_ptr<GameObject> Scene::root = make_shared<GameObject>(GameObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));


void Scene::update()
{
	
}

void Scene::renderUpdate()
{
	
}

void Scene::lightUpdate()
{
	
}


Scene::~Scene()
{
}
