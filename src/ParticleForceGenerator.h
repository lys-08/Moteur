/**
* \file particleForceGenerator.h
* This file contains the declaration of all methods and attributes of the ParticleForceGenerators class
*/

#pragma once

#include "vector3d.h"

class Particle;

class ParticleForceGenerator
{
public:
	virtual void updateForce(Particle* particle, float duration) = 0;
};