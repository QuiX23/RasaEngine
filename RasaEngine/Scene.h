#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Skybox.h"
#include "LightsManager.h"

#include <boost\container\map.hpp>
#include <boost\container\set.hpp>
#include <boost\functional\hash.hpp>
#include "PhysicsWorld.h"

namespace std
{
	template<>
	struct hash<UUID>
	{
		size_t operator () (const UUID& uid)
		{
			return boost::hash<UUID>()(uid);
		}
	};
}

class Scene
{
public:
	Scene();
	~Scene();

	Camera camera;
	
	/*  Scene Functions  */
	void update();
	void addComponent(shared_ptr<Component> component, const UUID & gameObject);
	void addRigidBody(std::shared_ptr<Collider> collider, const UUID & gameObject);
	void addSkybox(shared_ptr<Skybox> skybox);

	UUID addNewChild();
	UUID addNewChild(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale);
	UUID addNewChildToParent(UUID parentID);

	shared_ptr<GameObject> getGameObject(UUID goID);

	void renderObjects(glm::mat4 projection, glm::mat4 view);
	void renderObjects(glm::mat4 projection, glm::mat4 view, Shader shader);
	
private:
	/*  Scene data  */
	LightsManager lightsManager;
	PhysicsWorld physicsWorld;
	shared_ptr<GameObject> root;
	shared_ptr<Skybox> skybox;

	boost::container::map<UUID, shared_ptr<GameObject>> objectsCache;
	boost::container::set<UUID> renderableCompts;
	boost::container::set<UUID> rigidBodies;
	
	UUID addChild(shared_ptr<GameObject> parent);
	void addLight(shared_ptr<Component> component, const UUID & gameObject);
	void addRenderable(shared_ptr<Component> component, const UUID & gameObject);

	void renderUpdate();
	void renderSkybox(glm::mat4 projection, glm::mat4 view);

	void setViewProjection(glm::mat4 projection, glm::mat4 view);
};

