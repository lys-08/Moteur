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
	Vector3d newPos;
	switch (applyPoint_)
	{
	case '1':
		newPos = Vector3d(rigidBody->getMassCenter()->getPos().getX(),
			rigidBody->getMassCenter()->getPos().getY(),
			rigidBody->getMassCenter()->getPos().getZ() - 20);
		break;

	}
	rigidBody->addForceAtPoint(force_, newPos);
}
