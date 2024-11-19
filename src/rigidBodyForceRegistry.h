/**
* \file RigidBodyForceRegistry.h
* This file contains the declaration of all methods and attributes of the RigidBodyForceRegistry class
*/

#pragma once

#include "rigidBody.h"
#include "rigidBodyForceGenerator.h"


class RigidBodyForceRegistry
{
public:
	struct RigidBodyForceRegistration 
	{
		RigidBody* rigidBody;
		RigidBodyForceGenerator* forceGenerator;
	};

	typedef std::vector<RigidBodyForceRegistration> registry;

	registry registry_;

public:
	void add(RigidBody* RigidBody, RigidBodyForceGenerator* forceGenerator); 
	void remove(RigidBody* RigidBody, RigidBodyForceGenerator* forceGenerator);
	void clear();
	void updateForce(float duration);
};