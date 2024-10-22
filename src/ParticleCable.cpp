/**
* \file particleCable.cpp
* This file contains the implementation of all methods and attributes of the ParticleCable class
*/

#include "ParticleCable.h"

// TODO
/**
 * @brief Evaluated constructor
 *
 * @param particles 
 * @param maxLength
 */
ParticleCable::ParticleCable(Particle* particles[2], double maxLength)
{
	maxLength_ = maxLength;
	particles_[0] = particles[0];
	particles_[1] = particles[1];
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

// TODO
/**
 * @brief Add a contact for all particles in contacts
 *
 * @param contacts the paticles to add contacts
 * @param time
 * @return nothing
*/
void ParticleCable::addContact(std::vector<ParticleContact>& contacts, double time)
{
	if (getActualLength() > maxLength_)
	{
		Particle* particles[2];
		particles[0] = particles_[0];
		particles[1] = particles_[1];

		Vector3d normal = (particles[1]->getPos() - particles[0]->getPos()).normalise2();
		float interpretation = getActualLength() - maxLength_;

		ParticleContact contact = ParticleContact(particles, elasticity_, interpretation, normal);
		contacts.push_back(contact);
	}
}

// TODO
/**
 * @brief 
 *
 * @return 
*/
double ParticleCable::getActualLength() const
{
	return (particles_[0]->getPos() - particles_[1]->getPos()).norm();
}