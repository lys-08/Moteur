/**
* \file particleForceGenerator.h
* This file contains the declaration of all methods and attributes of the ParticleForceGenerators class
*/

#pragma once

#include "rigidBody.h"

class RigidBodyForceGenerator
{
public:
	virtual void updateForce(RigidBody* particle, float duration) = 0;
};