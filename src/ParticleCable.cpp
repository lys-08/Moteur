/**
* \file particleCable.cpp
* This file contains the implementation of all methods and attributes of the ParticleCable class
*/

#include "particleCable.h"


/**
 * @brief Evaluated constructor
 */
ParticleCable::ParticleCable(Particle* particles[2], double maxLength, double elasticity)
{
	maxLength_ = maxLength;
	elasticity_ = elasticity;
	particles_[0] = particles[0];
	particles_[1] = particles[1];
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief Add a contact for all particles in contacts
 *
 * @param contacts the paticles to add contacts
 * @param time
 * @return nothing
*/
void ParticleCable::addContact(std::vector<ParticleContact>& contacts, double time)
{
    double actualLength = getActualLength();

    // Si la longueur du câble dépasse la longueur maximale
    if (actualLength > maxLength_)
    {
        Particle* particles[2] = { particles_[0], particles_[1] };

        Vector3d normal = (particles[1]->getPos() - particles[0]->getPos()).normalise2();

        Vector3d relativeVelocity = particles[0]->getSpeed() - particles[1]->getSpeed();
        float relativeVelocityAlongNormal = relativeVelocity.dotProduct(normal);

        if (relativeVelocityAlongNormal <= 0)
        {
            ParticleContact contact(particles, elasticity_, 0, normal);
            
            contacts.push_back(contact);
        }
    }
}

/**
 * @brief 
 *
 * @return calculated length between the two particles
*/
double ParticleCable::getActualLength() const
{
	return (particles_[0]->getPos() - particles_[1]->getPos()).norm();
}