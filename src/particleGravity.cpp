/**
* \file particleGravity.cpp
* This file contains the implementation of all methods and attributes of the ParticleGravity class
*/

#include "particleGravity.h"



/**
 * @brief Default constructor
 */
ParticleGravity::ParticleGravity() : gravity_(0.0, -9.81, 0.0, 0.0) {}

/**
 * @brief Evaluated constructor
 */
ParticleGravity::ParticleGravity(const Vector3d& g) : gravity_(g) {}


/**
 * @brief Update the force for a particle according to the duration
 *
 * @param particle the particle we need to update the force
 * @param duration
 * @return the force of the particle
*/
void ParticleGravity::updateForce(Particle* particle, float duration)
{
    // We check if the particle has a valid mass (finite)
    if (particle->getInvertMass() <= 0.0f) return;

    double mass = 1.0 / particle->getInvertMass();
    Vector3d force = gravity_ * mass;
    particle->addForce(force);
}
