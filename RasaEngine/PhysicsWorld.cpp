#include "PhysicsWorld.h"
#include <GLFW/glfw3.h>


PhysicsWorld::PhysicsWorld()
{
	// Build the broadphase
	broadphase = new btDbvtBroadphase();

	// Set up the collision configuration and dispatcher
	collisionConfiguration =new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(&*collisionConfiguration);

	// The actual physics solver
	 solver =new btSequentialImpulseConstraintSolver();

	// The world.
	dynamicsWorld =new btDiscreteDynamicsWorld(&*dispatcher, &*broadphase, &*solver, &*collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

PhysicsWorld::~PhysicsWorld()
{
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}

void PhysicsWorld::addRigibody(btRigidBody* rigidBody) const
{
	dynamicsWorld->addRigidBody(rigidBody);
}

void PhysicsWorld::removeRigibody(btRigidBody* rigidBody) const
{
	dynamicsWorld->removeRigidBody(rigidBody);
}

void PhysicsWorld::stepSimulation() 
{
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	dynamicsWorld->stepSimulation(1 / 60.f, 10);
}
