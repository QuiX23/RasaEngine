#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "LightsManager.h"

#include <boost\container\map.hpp>
#include <boost\container\set.hpp>
#include <boost\functional\hash.hpp>



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
	UUID addNewChild();
	UUID addNewChild(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale);
	UUID addNewChildToParent(UUID parentID);
	

private:
	/*  Scene data  */
	LightsManager lightsManager;
	shared_ptr<GameObject> root;
	boost::container::map<UUID, shared_ptr<GameObject>> objectsCache;
	boost::container::set<UUID> renderableCompts;

	UUID addChild(shared_ptr<GameObject> parent);
	void addLight(shared_ptr<Component> component, const UUID & gameObject) ;
	void addRenderable(shared_ptr<Component> component, const UUID & gameObject) ;
	void lightUpdate();
	void renderUpdate() ;
	void renderObjects();
};

