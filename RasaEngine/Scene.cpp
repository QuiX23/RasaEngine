#pragma warning(disable : 4996)

#include "Scene.h"
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>  
#include <assert.h> 
#include <typeinfo>


shared_ptr<GameObject> Scene::root = make_shared<GameObject>(GameObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

 boost::container::map<UUID, shared_ptr<GameObject>> Scene::objectsCache;
 boost::container::set<UUID> Scene::lightCompts;
 boost::container::set<UUID> Scene::renderableCompts;

 Scene& Scene::getInstance()
 {
	 static Scene  instance; // Guaranteed to be destroyed.
									   // Instantiated on first use.
	 return instance;
 }


UUID Scene::addNewChild()
{
	return addChild(root);
}

void Scene::addComponent(shared_ptr<Component> component, const UUID & gameObject)
{
	
		if (component->type==ComponentType::Lights)
		{
			addLight(component, gameObject);
		}
		else if (component->type == ComponentType::Renderable)
		{
			addRenderable(component,gameObject);
		}
}

void Scene::addLight(shared_ptr<Component> component, const UUID & gameObject)
{
	if (objectsCache[gameObject]->HasComponent(ComponentType::Lights)) return;

	objectsCache[gameObject]->AddComponent(component);
	lightCompts.insert(gameObject);
}

void Scene::addRenderable(shared_ptr<Component> component, const UUID & gameObject)
{
	if (objectsCache[gameObject]->HasComponent(ComponentType::Renderable)) return;

	objectsCache[gameObject]->AddComponent(component);
	renderableCompts.insert(gameObject);
}



UUID Scene::addChild(shared_ptr<GameObject> parent)
{
	shared_ptr<GameObject> newObject = make_shared<GameObject>(GameObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	newObject->uid = boost::uuids::random_generator()();
	newObject->parent = root;
	root->children.push_back(newObject);
	
	assert(objectsCache.find(newObject->uid)==objectsCache.end());
	
	objectsCache[newObject->uid] = newObject;
	return newObject->uid;
}

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
