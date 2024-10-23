#pragma once

#include "particle.h"
#include "particleContactGenerator.h"
#include "particleSphericalCollisionGenerator.h"
#include "particleRestCollisionGenerator.h"
#include "particleStraightCable.h"
#include "particleForceRegistry.h"
#include "particleGravity.h"
#include "particleFriction.h"
#include "particleSetSpring.h"
#include "particleStraightCable.h"
#include "particleCable.h"

class World
{
private:
	std::vector<ParticleContact> contacts_;
	std::vector<ParticleContactGenerator*> contactGenerators_;
	ParticleSphericalCollisionGenerator* collisionSphere;
	ParticleRestCollisionGenerator* collisionRest;
	Plane ground_ = Plane(Vector3d(0,-1,0,0),Vector3d(950,950,0,1));

	ParticleForceRegistry forcesRegistry_;
	ParticleGravity g_;
	ParticleFriction friction_;
	ParticleSpring* springForce;

public:
	std::vector<Particle*> particles_;
	std::vector<Particle*> originalBlob;
	std::vector<Particle*> secondBlob;

	World();
	void start(int x,int y);
	void attachNewParticle();
	void update(double time);
	void addParticle(Particle* particle);
	void addContactGenerator(ParticleContactGenerator* generator);
	void checkForRupture();
	void separateBlob();
	void reformBlob();
	void updateForces(double time);
	void generateContacts();
	void solveContacts(double duration);
	void integrate(double time);
	void resetAcc();
};

