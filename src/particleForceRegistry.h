/**
* \file particleForceRegistry.h
* This file contains the declaration of all methods and attributes of the ParticleForceRegistry class
*/

#pragma once

#include "particle.h"
#include "particleForceGenerator.h"


class ParticleForceRegistry
{
public:
	struct ParticleForceRegistration 
	{
		Particle* particle;
		ParticleForceGenerator* forceGenerator;
	};
	typedef std::vector<ParticleForceRegistration> registry;

	registry registry_;

public:
	void add(Particle* particle, ParticleForceGenerator* forceGenerator); // add a particle to the registry
	void remove(Particle* particle, ParticleForceGenerator* forceGenerator); // remove a particle from the registry
	void clear();															 // clear the registry
	void updateForce(float duration);										 // update the force according to the time
};