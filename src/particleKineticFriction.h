/**
* \file particleKineticFriction.h
* This file contains the declaration of all methods and attributes of the ParticleKineticFriction class
*/

#pragma once

#include "ParticleForceGenerator.h"
#include "Particle.h"
#include "Plane.h"

class ParticleKineticFriction
	: public ParticleForceGenerator
{
private:
	float mu_k; // Cinetic friction coefficient
	Plane surfacePlane_;

public:
	ParticleKineticFriction(float coefficient = 0.3f, Plane surface = Plane());

	virtual void updateForce(Particle* particle, float duration) override;
};

