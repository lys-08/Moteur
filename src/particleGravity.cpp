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
    std::cout << "gravity" << std::endl;

    // We check if the particle has a valid mass (finite)
    if (particle->getInvertMass() <= 0.0f) return;

    double mass = 1.0 / particle->getInvertMass();
    Vector3d force = gravity_ * mass;
    std::cout << force << "\n" << std::endl;
    //particle->addForce(force);
    Vector3d newPos = Vector3d(particle->getPos().getX()+20, particle->getPos().getY(), particle->getPos().getZ()+20);
    particle->getRigidBody()->addForceAtPoint(force, newPos);
}
