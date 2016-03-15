#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <memory>
#include <map>

using namespace std;

class GameObject
{

public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	shared_ptr<Component> GetComponent(ComponentType type);
	void AddComponent(shared_ptr<Component> component);
	bool HasComponent(ComponentType type);

private:
	glm::mat4 modelMatrix;
	
	std::map<ComponentType, shared_ptr<Component>> m_components;
	GameObject();
	~GameObject();
};

