#pragma once

#include "ParticleForceGenerator.h"
#include "Particle.h"

class particleKineticFriction
	: public ParticleForceGenerator
{
private:
	float mu_k;  // Cinetic friction coefficient

public:
	// Default constructor with a standard friction coefficient
	particleKineticFriction();

	// Constructor with a custom friction coefficient
	particleKineticFriction(float coefficient);

	// Method to apply cinetic friction force
	virtual void updateForce(Particle* particle, float duration) override;

};

