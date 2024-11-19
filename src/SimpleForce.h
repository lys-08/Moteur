/**
* \file SimpleForce.h
* This file contains the declaration of all methods and attributes of the SimpleForce class
*/
#pragma once

#include "rigidBodyForceGenerator.h"
#include "vector3d.h"

class SimpleForce :
	public RigidBodyForceGenerator
{
	Vector3d force_;
	int applyPoint_;
	Vector3d newPos_;

public:
	SimpleForce(const Vector3d& f = Vector3d(0.0, 0.0, 0.0, 0.0),int a = 1);
	void updateForce(RigidBody* rigidBody, float duration);
};
