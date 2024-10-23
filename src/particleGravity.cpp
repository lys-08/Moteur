/**
* \file particleGravity.cpp
* This file contains the implementation of all methods and attributes of the ParticleGravity class
*/

#include "particleGravity.h"
#include "particle.h"



/**
 * @brief Default and evaluated constructor
 */
ParticleGravity::ParticleGravity(const Vector3d& g) 
{
    gravity_ = g;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief Update the force for a particle according to the duration
 *
 * @param particle the particle whose force is to be updated
 * @param duration
*/
void ParticleGravity::updateForce(Particle* particle, float duration)
{
    // We check if the particle has a valid mass (finite)
    if (particle->getInvertMass() <= 0.0f) return;

    double mass = 1.0 / particle->getInvertMass();
    Vector3d force = gravity_ * mass;
    particle->addForce(force);
}
