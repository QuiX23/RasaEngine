#pragma once
#include "Component.h"
#include "Collider.h"
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>

class PhysicsWorld;

class RigidBody :
	public Component
{
public:
	RigidBody();
	RigidBody(const btVector3& position,const btQuaternion& rotation, std::shared_ptr<Collider> collider,PhysicsWorld* physicsWorld);
	~RigidBody();
	void setAsDynamic();
	btTransform getTransform() const;
	bool isDynamic() const
	{ return dynamic; };
private:
	bool dynamic=false;
	float mass=1.0f;
	PhysicsWorld* physicsWorld;
	std::shared_ptr<Collider> collider;
	
	btRigidBody* rigidBody;
	btDefaultMotionState* motionState;
	btRigidBody::btRigidBodyConstructionInfo* info;
};

