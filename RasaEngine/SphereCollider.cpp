#include "SphereCollider.h"
#include <BulletCollision/CollisionShapes/btSphereShape.h>


SphereCollider::SphereCollider(float radius)
{
	shape = std::make_shared <btSphereShape>(btSphereShape(radius));
}


SphereCollider::~SphereCollider()
{
}
