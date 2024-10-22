#pragma once

#include "particle.h"
#include "ParticleContactGenerator.h"
#include "ParticleSphericalCollisionGenerator.h"
#include "ParticleRestCollisionGenerator.h"
#include "ParticleStraightCable.h"
#include "ParticleForceRegistry.h"
#include "particleGravity.h"
#include "particleKineticFriction.h"
#include "particleStaticFriction.h"
#include "ParticleSetSpring.h"

class World
{
private:
	std::vector<ParticleContact> contacts_;
	std::vector<ParticleContactGenerator*> contactGenerators_;
	ParticleSphericalCollisionGenerator* collisionSphere;
	ParticleRestCollisionGenerator* collisionRest;
	Plane ground_ = Plane(Vector3d(0,-1,0),Vector3d(950,950,0));

	ParticleForceRegistry forcesRegistry_;
	ParticleGravity g_;
	ParticleKineticFriction fk_;
	ParticleStaticFriction fs_;
	ParticleSetSpring* setSpringForce;

public:
	std::vector<Particle*> particles_;

	World();
	void start();
	void update(double time);
	void addParticle(Particle* particle);
	void addContactGenerator(ParticleContactGenerator* generator);
	void addSpringForce(ParticleForceGenerator* forceGenerator, Particle* particle);
	void updateForces(double time);
	void generateContacts();
	void solveContacts(double duration);
	void integrate(double time);
	void resetAcc();
};

