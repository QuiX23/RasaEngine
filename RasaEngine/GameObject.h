#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <memory>
#include <map>
#include <vector>

using namespace std;

class GameObject
{

public:
	/*GameObject variables*/
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	/*GameObject tree variables*/
	shared_ptr<GameObject> parent;
	vector <shared_ptr<GameObject>> children;
	/*GameObject functions*/
	shared_ptr<Component> GetComponent(ComponentType type);
	void AddComponent(shared_ptr<Component> component);
	bool HasComponent(ComponentType type);

	GameObject();
	GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~GameObject();

private:
	glm::mat4 modelMatrix;
	std::map<ComponentType, shared_ptr<Component>> m_components;

};

