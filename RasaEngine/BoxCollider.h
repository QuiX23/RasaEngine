#pragma once
#include "Collider.h"
class btVector3;

class BoxCollider :
	public Collider
{
public:
	BoxCollider(const btVector3 & size);

	~BoxCollider();
};

