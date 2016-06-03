#pragma once
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics\Dynamics\btDiscreteDynamicsWorld.h"
#include "BulletDynamics\ConstraintSolver\btSequentialImpulseConstraintSolver.h"

class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void addRigibody(btRigidBody* rigidBody) const;
	void removeRigibody(btRigidBody* rigidBody) const;
	void stepSimulation();
private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	float lastTime = 0.0f;
};

