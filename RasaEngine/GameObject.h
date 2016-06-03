#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <memory>
#include <map>
#include <vector>

#include <boost/uuid/uuid.hpp>            // uuid class

class PhysicsWorld;
class Collider;
using namespace std;

class GameObject
{

public:
	/*GameObject variables*/
	boost::uuids::uuid  uid;
	string name;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec4 rotation;
	/*GameObject tree variables*/
	shared_ptr<GameObject> parent;
	vector <shared_ptr<GameObject>> children;
	/*GameObject functions*/
	shared_ptr<Component> GetComponent(ComponentType type);
	void AddComponent(shared_ptr<Component> component);
	void AddRigidBody(std::shared_ptr<Collider> collider, PhysicsWorld* physicsWorld);
	bool HasComponent(ComponentType type);

	GameObject();
	GameObject(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale);
	~GameObject();

private:
	glm::mat4 modelMatrix;
	map<ComponentType, shared_ptr<Component>> m_components;

};

