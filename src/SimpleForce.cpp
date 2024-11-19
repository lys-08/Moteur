/**
* \file SimpleForce.cpp
* This file contains the implementation of all methods and attributes of the SimpleForce class
*/

#include "SimpleForce.h"
#include "particle.h"

SimpleForce::SimpleForce(const Vector3d& f)
{
	force_ = f;
}

void SimpleForce::updateForce(Particle* particle, float duration)
{
    if (particle->getInvertMass() <= 0.0f) return;
	Vector3d newPos = Vector3d(particle->getPos().getX() +20, particle->getPos().getY(), particle->getPos().getZ()-20);
	particle->getRigidBody()->addForceAtPoint(force_, newPos);
}
