#include "PlaneCollider.h"
#include <memory>
#include <BulletCollision/CollisionShapes/btStaticPlaneShape.h>


PlaneCollider::PlaneCollider(const btVector3 &  planeNormal, float planeConstant)
{
	shape = std::make_shared<btStaticPlaneShape>(planeNormal, planeConstant);
}

PlaneCollider::~PlaneCollider()
{
}
