/**
* \file particleForceRegistry.h
* This file contains the declaration of all methods and attributes of the ParticleForceRegistry class
*/

#pragma once

#include "particle.h"
#include "particleForceGenerator.h"


class ParticleForceRegistry
{
	struct ParticleForceRegistration 
	{
		Particle* particle_;
		ParticleForceGenerator* strengthGenerator;
	};
	typedef std::vector<ParticleForceRegistration> registry;

public:
	void add(const Particle &particle, ParticleForceGenerator &registry);	// TODO
	void remove(const Particle& particle, ParticleForceGenerator& registry);// TODO
	void clear();															// TODO
	void updateForce(float duration);										// TODO
};