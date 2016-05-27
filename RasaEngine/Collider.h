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
	std::shared_ptr<btCollisionShape> getShape() const
	{ return shape; };
protected:
	std::shared_ptr<btCollisionShape> shape;
};

