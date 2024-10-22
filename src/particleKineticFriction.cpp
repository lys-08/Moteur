/**
* \file particleKineticFriction.cpp
* This file contains the implementation of all methods and attributes of the ParticleKineticFriction class
*/

#include "ParticleKineticFriction.h"



/**
 * @brief Default and evaluated constructor
 */
ParticleKineticFriction::ParticleKineticFriction(float coefficient, Plane surface)
{
	mu_k = 0.3f;
    surfacePlane_ = surface;
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
void ParticleKineticFriction::updateForce(Particle* particle, float duration)
{
    // Check if the particle has finite mass (if invMass = 0, it's infinite mass)
    if (particle->getInvertMass() <= 0.0f) return;

    Vector3d velocity = particle->getSpeed();

    // Check if the particle is moving; no need to apply kinetic friction if velocity is zero
    if (velocity.norm() == 0.0f) return;

    double mass = 1.0 / particle->getInvertMass();
	Vector3d normalForce = Vector3d(0, -45, 0); // We chose a normal force of 20N

    float frictionMagnitude = normalForce.norm() * mu_k;
    Vector3d frictionForce = velocity.normalise2() * -frictionMagnitude;

    particle->addForce(frictionForce);
}
