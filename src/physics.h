/**
* \file physics.h
* This file contains the declaration of all methods and attributes of the Physics class
*/

#pragma once

#include "rigidBody.h"
#include "rigidbodyContact.h"
#include "rigidBodyForceRegistry.h"
#include "rigidBodyGravity.h"
#include "SimpleForce.h"
#include "OcTree.h"

class Physics
{
private:
	double width_;
	double height_;
	RigidBodyForceRegistry forcesRegistry_;
	RigidBodyGravity g_;
	std::vector<SimpleForce> simpleForces_;
	std::vector<RigidBodyContact> contacts_;

public:
	std::vector<RigidBody*> objects_;
	OcTree octree;

	Physics();
	void start(int x, int y);
	void deleteOutOfBounds();
	void fillTree();
	void update(double time);
	void addRigidBody(RigidBody* rigidBody);
	void addSimpleForce(SimpleForce force);
	void updateForces(double time);
	void integrate(double time);
	void generateContacts();
	void solveContacts(double duration);
	void resetAcc();
};

