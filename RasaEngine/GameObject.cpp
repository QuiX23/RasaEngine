#include "GameObject.h"

shared_ptr<Component> GameObject::GetComponent(ComponentType type)
{

	return m_components[type];
}
void GameObject::AddComponent( shared_ptr<Component> component)
{
	m_components[component->type] = component;
}
bool GameObject::HasComponent(ComponentType type)
{

	if (m_components.find(type) == m_components.end())
		return false;
	return true;
}


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}
