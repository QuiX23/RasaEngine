#pragma warning(disable : 4996)

#include "Scene.h"
#include "Model.h"
#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>  
#include <assert.h> 




Camera Scene::camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

Scene& Scene::getInstance()
{
	static Scene  instance; // Guaranteed to be destroyed.
							// Instantiated on first use.
	return instance;
}

shared_ptr<GameObject> Scene::root = make_shared<GameObject>(GameObject(glm::vec3(0, 0, 0), glm::vec4(0, 0, 0, 0), glm::vec3(1, 1, 1)));

boost::container::map<UUID, shared_ptr<GameObject>> Scene::objectsCache;
boost::container::set<UUID> Scene::renderableCompts;


LightsManager Scene::lightsManager = LightsManager();

UUID Scene::addNewChild()
{
	
	return addChild(root);
}

UUID Scene::addNewChild(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale)
{
	UUID id = addChild(root);
	objectsCache[id]->position = position;
	objectsCache[id]->rotation = rotation;
	objectsCache[id]->scale = scale;
	return id;
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

	shared_ptr<C_Light> m = static_pointer_cast<C_Light>(component);
	m->position = objectsCache[gameObject]->position;

	objectsCache[gameObject]->AddComponent(component);
	
	lightsManager.addLight(static_pointer_cast<C_Light>(component));
}

void Scene::addRenderable(shared_ptr<Component> component, const UUID & gameObject)
{
	if (objectsCache[gameObject]->HasComponent(ComponentType::Renderable)) return;

	shared_ptr<Model> m = static_pointer_cast<Model>(component);

	objectsCache[gameObject]->AddComponent(component);
	renderableCompts.insert(gameObject);
}



UUID Scene::addChild(shared_ptr<GameObject> parent)
{
	shared_ptr<GameObject> newObject = make_shared<GameObject>(GameObject(glm::vec3(0, 0, 0), glm::vec4(0, 0, 0,0), glm::vec3(1, 1, 1)));
	newObject->uid = boost::uuids::random_generator()();
	newObject->parent = root;
	root->children.push_back(newObject);
	
	assert(objectsCache.find(newObject->uid)==objectsCache.end());
	
	objectsCache[newObject->uid] = newObject;
	return newObject->uid;
}

void Scene::update()
{
	renderUpdate();
}

void Scene::renderUpdate()
{
	for each (UUID var in renderableCompts)
	{
		
		shared_ptr<Model> ptr = static_pointer_cast<Model>(objectsCache[var]->GetComponent(ComponentType::Renderable));
		ptr->shader.Use();

		// Transformation matrices
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)(Context::getInstance().screenWidth) / (float)(float)(Context::getInstance().screenHeight), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(ptr->shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(ptr->shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		
		glUniform3f(glGetUniformLocation(ptr ->shader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	
		lightsManager.activateLights(ptr->shader);

		glm::mat4 model;
		model = glm::translate(model, objectsCache[var]->position); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, objectsCache[var]->scale);	// It's a bit too big for our scene, so scale it down
		model = glm::rotate(model, objectsCache[var]->rotation.w, glm::vec3(objectsCache[var]->rotation));	// It's a bit too big for our scene, so scale it down

		glUniformMatrix4fv(glGetUniformLocation(ptr->shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		ptr->draw(*Context::getInstance().renderer);
	}
}

void Scene::lightUpdate()
{
	
}


Scene::~Scene()
{
}
