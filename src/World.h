#pragma once

#include "particle.h"
#include "ParticleContactGenerator.h"
#include "ParticleForceRegistry.h"

class World
{
private:
	std::vector<Particle*> particles_;
	std::vector<ParticleContactGenerator*> contactGenerators_;
	std::vector<ParticleForceRegistry*> forces_;

public:
	void update(double time);
	void addParticle(Particle* particle);
	void updateForces(double time);
	std::vector<ParticleContact>& generateContacts();
	void solveContacts(std::vector<ParticleContact>& contacts, double duration);
	void integrate(double time);
	void resetAcc();
};

