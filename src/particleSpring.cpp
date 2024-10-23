/**
* \file particleSpring.cpp
* This file contains the implementation of all methods and attributes of the ParticleSpring class
*/

#include "particleSpring.h"
#include "particle.h"



/**
 * @brief Evaluated constructor
 */
ParticleSpring::ParticleSpring()
{
}

ParticleSpring::ParticleSpring(Particle* other, double k, double l0)
{
    other_ = other;
    k_ = k;
    l0_ = l0;
}


/**
 * @brief Update the force for a particle according to the duration
 *
 * @param particle the particle we need to update the force
 * @param duration
 * @return the force of the particle
*/
void ParticleSpring::updateForce(Particle* particle, float duration)
{
	Vector3d dist = other_->getPos() - particle->getPos();
	double norm = dist.norm();

	Vector3d force = - k_ * (l0_ - norm) * dist.normalise2(); // Hooke's law : F = k * (l0 - l) * u
	
	particle->addForce(force);
}
