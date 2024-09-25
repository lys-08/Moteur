#pragma once

#include "src/particle.h"

class ParticleForceGenerator
{
public:
	virtual void updateForce(Particle* particle, float duration) = 0;
};