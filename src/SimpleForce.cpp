/**
* \file SimpleForce.cpp
* This file contains the implementation of all methods and attributes of the SimpleForce class
*/

#include "SimpleForce.h"
#include "particle.h"

SimpleForce::SimpleForce(const Vector3d& f, int a)
{
	force_ = f;
	applyPoint_ = a;
}

void SimpleForce::updateForce(RigidBody* rigidBody, float duration)
{
	if (applyPoint_ == 1)
	{
		newPos_ = Vector3d(rigidBody->getMassCenter()->getPos().getX(),
			rigidBody->getMassCenter()->getPos().getY(),
			rigidBody->getMassCenter()->getPos().getZ() - 20);
	}
	else if (applyPoint_ == 2)
	{
		newPos_ = Vector3d(rigidBody->getMassCenter()->getPos().getX(),
			rigidBody->getMassCenter()->getPos().getY() - 20,
			rigidBody->getMassCenter()->getPos().getZ());
	}
	else if (applyPoint_ == 3)
	{
		newPos_ = Vector3d(rigidBody->getMassCenter()->getPos().getX() - 20,
			rigidBody->getMassCenter()->getPos().getY(),
			rigidBody->getMassCenter()->getPos().getZ());
	}

	rigidBody->addForceAtPoint(force_, newPos_);
}
