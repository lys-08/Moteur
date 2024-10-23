/**
* \file particleFriction.h
* This file contains the declaration of all methods and attributes of the ParticleFriction class
*/

#pragma once

#include "particleForceGenerator.h"
#include "particle.h"
#include "plane.h"

class ParticleFriction
	: public ParticleForceGenerator
{
private:
	float k1_;
	float k2_;

public:
	ParticleFriction(float k1_ = 0.1f, float k2_ = 0.1f);

	virtual void updateForce(Particle* particle, float duration) override;
};

