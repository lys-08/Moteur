/**
* \file particleRestCollisionGenerator.cpp
* This file contains the implementation of all methods and attributes of the ParticleRestCollisionGenerator class
*/

#include "particleRestCollisionGenerator.h"


/**
 * @brief Evaluated constructor
 */
ParticleRestCollisionGenerator::ParticleRestCollisionGenerator(Plane ground)
{
	ground_ = ground;
}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

void ParticleRestCollisionGenerator::setParticles(std::vector<Particle*> particles)
{
	particles_ = particles;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief generate a contact if a particle is on the plane
 *
 * @param contacts list of all the contacts at a frame
 * @param time
 * @return nothing
*/
void ParticleRestCollisionGenerator::addContact(std::vector<ParticleContact>& contacts, double time)
{
    int size = particles_.size();
    for (int i = 0; i < size; i++)
    {
        double distanceToPlane = (particles_[i]->getPos() - ground_.getPoint()).dotProduct(ground_.getNormal());

        if (distanceToPlane < particles_[i]->getRadius() && distanceToPlane > -particles_[i]->getRadius())
        {
            double projectedSpeed = particles_[i]->getSpeed().dotProduct(ground_.getNormal());
            Vector3d acceleration = particles_[i]->getForceAccum() * particles_[i]->getInvertMass();
            double projectedAcceleration = acceleration.dotProduct(ground_.getNormal());

            if (projectedAcceleration * time > projectedSpeed)
            {
                Particle* particles[2];
                particles[0] = particles_[i];
                particles[1] = nullptr;

                ParticleContact contact = ParticleContact(particles, 0.5, distanceToPlane - particles[0]->getRadius(), ground_.getNormal());
                contacts.push_back(contact);
            }
        }
    }
}

