/**
* \file rigidbodyContact.h
* This file contains the declaration of all methods and attributes of the RigidBodyContact class
*/

#pragma once

#include "rigidBody.h"

class RigidBodyContact
{
	RigidBody* rigidBodies_[2];

	float elasticity_; // elasticity of the contact (0 = no elasticity, 1 = perfect elasticity)
	float interpenetration_; // the amount of interpenetration between the two particles 
	Vector3d normal_;
	Vector3d contactPoint_;

public:
	RigidBodyContact(RigidBody* rigidBodies[2], float elasticity, float interpenetration, Vector3d contactPoint, Vector3d normal);
	void solve();
};