#pragma once

#include "particle.h"
#include "ParticleContactGenerator.h"
#include "ParticleSphericalCollisionGenerator.h"
#include "ParticleForceRegistry.h"
#include "particleGravity.h"

class World
{
private:

	std::vector<ParticleContact> contacts_;
	std::vector<ParticleContactGenerator*> contactGenerators_;
	ParticleSphericalCollisionGenerator* collisionSphere;

	ParticleForceRegistry forcesRegistry_;
	ParticleGravity g_;

public:
	std::vector<Particle*> particles_;

	World();
	void start();
	void update(double time);
	void addParticle(Particle* particle);
	void updateForces(double time);
	void generateContacts();
	void solveContacts(double duration);
	void integrate(double time);
	void resetAcc();
};

