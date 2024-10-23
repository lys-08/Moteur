/**
* \file particleFriction.cpp
* This file contains the implementation of all methods and attributes of the ParticleFriction class
*/

#include "particleFriction.h"



/**
 * @brief Default and evaluated constructor
 */
ParticleFriction::ParticleFriction(float k1, float k2)
{
	k1_ = k1;
    k2_ = k2;
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
void ParticleFriction::updateForce(Particle* particle, float duration)
{
    Vector3d speed = particle->getSpeed();
    if (speed.norm() == 0.0f) return; // If the particle isn't moving; no need to apply kinetic friction

    Vector3d force = - (k1_ * speed.norm() + k2_ * speed.norm2()) * speed.normalise2();
    particle->addForce(force);
}
