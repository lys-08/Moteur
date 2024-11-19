/**
* \file SimpleForce.h
* This file contains the declaration of all methods and attributes of the SimpleForce class
*/

#include "particleForceGenerator.h"
#include "vector3d.h"

class SimpleForce :
	public ParticleForceGenerator
{
	Vector3d force_;

public:
	SimpleForce(const Vector3d& f = Vector3d(0.0, 0.0, 0.0, 0.0));

	void updateForce(Particle* particle, float duration);
};
