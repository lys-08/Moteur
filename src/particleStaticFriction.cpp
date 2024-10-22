/**
* \file particleStaticFriction.cpp
* This file contains the implementation of all methods and attributes of the ParticleStaticFriction class
*/

#include "particleStaticFriction.h"


/**
 * @brief Default and evaluated constructor
 */
ParticleStaticFriction::ParticleStaticFriction(float coefficient, Plane plane)
{
	mu_s_ = coefficient;
    surfacePlane_ = plane;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

// TODO
/**
 * @brief
 *
 * @param particle
 * @param duration
 * @return nothing
*/
void ParticleStaticFriction::updateForce(Particle* particle, float duration)
{
    // Check if the particle has finite mass (if invMass = 0, it's infinite mass)
    if (particle->getInvertMass() <= 0.0f) return;

    // Get the accumulated force applied to the particle
    Vector3d appliedForce = particle->getForceAccum(); 
    
    Vector3d surfaceNormal = Vector3d(0, -1, 0);
    surfaceNormal.normalise();

    double mass = 1.0 / particle->getInvertMass();
    Vector3d gravityForce = Vector3d(0.0f, mass * 9.81f, 0.0f); // N = m * g 
    Vector3d normalForce =  surfaceNormal * (gravityForce.dotProduct(surfaceNormal));

    Vector3d maxStaticFriction = normalForce * mu_s_;

    Vector3d tangentialForce = appliedForce - surfaceNormal * appliedForce.dotProduct(surfaceNormal);

    /* If the applied force is less than or equal to the static friction force,
    apply an opposite force to cancel out the movement (neutralize the force) */
    if (tangentialForce.norm() <= maxStaticFriction.norm())
    {
        tangentialForce *= -1;
        particle->addForce(appliedForce);
    } 

}
