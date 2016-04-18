#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "LightsManager.h"

#include <boost\container\map.hpp>
#include <boost\container\set.hpp>
#include <boost\functional\hash.hpp>


typedef boost::uuids::uuid UUID;

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
	static Camera camera;
	/*Singleton pattern methods*/
	static Scene& getInstance();
	void operator=(Scene const&) = delete;
	Scene(Scene const&) = delete;
	~Scene();

	/*  Scene Functions  */
	void update();
	void addComponent(shared_ptr<Component> component, const UUID & gameObject);
	UUID addNewChild();
	UUID addNewChild(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale);
	UUID addNewChildToParent(boost::uuids::uuid parentID);
	

private:
	/*  Scene data  */
	static LightsManager lightsManager;
	static shared_ptr<GameObject> root;
	static boost::container::map<UUID, shared_ptr<GameObject>> objectsCache;
	static boost::container::set<UUID> renderableCompts;

	UUID addChild(shared_ptr<GameObject> parent);
	void addLight(shared_ptr<Component> component, const UUID & gameObject);
	void addRenderable(shared_ptr<Component> component, const UUID & gameObject);
	void lightUpdate();
	void renderUpdate() const;

	Scene() {};

};

