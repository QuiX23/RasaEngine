#include "GameObject.h"
#include "Collider.h"
#include "RigidBody.h"

shared_ptr<Component> GameObject::GetComponent(ComponentType type)
{

	return m_components[type];
}
void GameObject::AddComponent( shared_ptr<Component> component)
{
	m_components[component->type] = component;
}

void GameObject::AddRigidBody(std::shared_ptr<Collider> collider, PhysicsWorld* physicsWorld)
{
	shared_ptr<Component> rigidBody = make_shared<RigidBody>(btVector3(position.x, position.y, position.z),
															btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
															collider, physicsWorld);
	AddComponent(rigidBody);
}

bool GameObject::HasComponent(ComponentType type)
{
	if (m_components.find(type) == m_components.end())
		return false;
	return true;
}


GameObject::GameObject()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec4(0, 0, 0,1);
	scale = glm::vec3(1, 1, 1);
	name = "default";
}

GameObject::GameObject(glm::vec3 position, glm::vec4 rotation, glm::vec3 scale)
	: position(position), rotation(rotation), scale(scale)
{
	name = "default";
}


GameObject::~GameObject()
{
}
