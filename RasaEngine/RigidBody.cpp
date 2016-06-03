#include "RigidBody.h"
#include <LinearMath/btDefaultMotionState.h>
#include "PhysicsWorld.h"


RigidBody::RigidBody(): Component(ComponentType_RigidBody)
{
}

RigidBody::RigidBody(const btVector3&position, const btQuaternion& rotation, std::shared_ptr<Collider> collider, PhysicsWorld* physicsWorld) : Component(ComponentType_RigidBody)
{
	this->collider = collider;
	this->physicsWorld = physicsWorld;

	motionState =new btDefaultMotionState(btTransform(rotation, position));

	info=new  btRigidBody::btRigidBodyConstructionInfo(0,&* motionState, &*(collider->getShape()));

	rigidBody = new btRigidBody(*info);
	physicsWorld->addRigibody(&*rigidBody);
}

RigidBody::~RigidBody()
{
	delete rigidBody;
	delete motionState;
	delete info;
}

void RigidBody::setAsDynamic()
{
	dynamic = true;
	
	btVector3 fallInertia(0, 0, 0);
	collider->getShape()->calculateLocalInertia(mass, fallInertia);

	info=new  btRigidBody::btRigidBodyConstructionInfo(mass, &* motionState, &*(collider->getShape()));
	
	physicsWorld->removeRigibody(&*rigidBody);
	
	rigidBody = new btRigidBody(*info);
	physicsWorld->addRigibody(&*rigidBody);
}

btTransform RigidBody::getTransform() const
{
	btTransform trans;
	rigidBody->getMotionState()->getWorldTransform(trans);
	//cout << rigidBody->m_mass;
	return  trans;
}
