#pragma once

#include "rigidBody.h"
#include "rigidBodyForceRegistry.h"
#include "rigidBodyGravity.h"
#include "SimpleForce.h"
#include "OcTree.h"

class Physics
{
private:
	RigidBodyForceRegistry forcesRegistry_;
	RigidBodyGravity g_;
	std::vector<SimpleForce> simpleForces_;

public:
	std::vector<RigidBody*> objects_;
	OcTree octree;

	Physics();
	void start(int x, int y);
	void update(double time);
	void addRigidBody(RigidBody* rigidBody);
	void addSimpleForce(SimpleForce force);
	void updateForces(double time);
	void integrate(double time);
	void resetAcc();
};

