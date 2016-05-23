#pragma once
#include "Component.h"
#include<memory>
class btCollisionShape;
class Collider :
	public Component
{
public:
	Collider();
	~Collider();
protected:
	std::shared_ptr<btCollisionShape> shape;
};

