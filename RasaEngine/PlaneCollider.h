#pragma once
#include "Collider.h"
class btVector3;

class PlaneCollider :
	public Collider
{
public:
	PlaneCollider(const btVector3 & planeNormal,float planeConstant);
	~PlaneCollider();
};

