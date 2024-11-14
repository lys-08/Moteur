#pragma once

#include "rigidBody.h"
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

class Physics
{
private:
	Plane ground_ = Plane(Vector3d(0, -1, 0, 0), Vector3d(950, 950, 0, 1));

	ParticleForceRegistry forcesRegistry_;
	ParticleGravity g_;
	ParticleFriction friction_;
	ParticleSpring* springForce;

public:
	std::vector<RigidBody*> objects_;

	Physics();
	void start(int x, int y);
	void update(double time);
	void addRigidBody(RigidBody* particle);
	void updateForces(double time);
	void integrate(double time);
	void resetAcc();
};

