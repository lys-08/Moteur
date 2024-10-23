/**
* \file particleSetSpring.cpp
* This file contains the implementation of all methods and attributes of the ParticleSetSpring class
*/

#include "particleSetSpring.h"
#include "particle.h"


/**
 * @brief Evaluated constructor
 */
ParticleSetSpring::ParticleSetSpring()
{
}

ParticleSetSpring::ParticleSetSpring(Vector3d point, double k, double l0)
{
    point_ = point;
    k_ = k;
    l0_ = l0;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief add the force "spring anchored to a point" in the particle
 *
 * @param particle
 * @param duration
 * @return nothing
*/
void ParticleSetSpring::updateForce(Particle* particle, float duration)
{
    Vector3d dist = point_ - particle->getPos();
    double norm = dist.norm();

    Vector3d force = - k_ * (l0_ - norm) * dist.normalise2();
    particle->addForce(force);
}
