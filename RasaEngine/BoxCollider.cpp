#include "BoxCollider.h"
#include <BulletCollision/CollisionShapes/btBoxShape.h>


BoxCollider::BoxCollider(const btVector3 & size)
{
	shape = std::make_shared <btBoxShape>(btBoxShape(size));
}

BoxCollider::~BoxCollider()
{
}
