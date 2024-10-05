/**
* \file gravity.cpp
* This file contains the implementation of all methods and attributes of the Gravity class
*/

#include "gravity.h"



/**
 * @brief Default constructor
 */
Gravity::Gravity() : gravity(0.0, -9.81, 0.0, 0.0) {}

/**
 * @brief Evaluated constructor
 */
Gravity::Gravity(const Vector3d& g) : gravity(g) {}


/**
 * @brief Update the force for a particle according to the duration
 *
 * @param particle the particle we need to update the force
 * @param duration
 * @return the dot product
*/
void Gravity::updateForce(Particle* particle, float duration)
{
    // We check if the particle has a valid mass (finite)
    if (particle->getInvertMass() <= 0.0f) return;

    // Get the mass from the inverse mass
    double mass = 1.0 / particle->getInvertMass();

    // Calculate the gravitational force
    Vector3d force = gravity * mass;

    // Apply the force to the particle
    particle->addForce(force);
}
