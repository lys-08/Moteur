/**
* \file particleRestCollisionGenerator.cpp
* This file contains the implementation of all methods and attributes of the ParticleRestCollisionGenerator class
*/

#include "ParticleRestCollisionGenerator.h"


/**
 * @brief Evaluated constructor
 */
ParticleRestCollisionGenerator::ParticleRestCollisionGenerator(Plane ground)
{
	ground_ = ground;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

// TODO
/**
 * @brief 
 *
 * @param contacts
 * @param time
 * @return nothing
*/
void ParticleRestCollisionGenerator::addContact(std::vector<ParticleContact>& contacts, double time)
{
	int size = particles_.size();
	for (int i = 0; i < size; i++)
	{
		double projectedSpeed = particles_[i]->getSpeed().dotProduct(ground_.getNormal());
		Vector3d acceleration = particles_[i]->getForceAccum() * particles_[i]->getInvertMass();
		double projectedAcceleration = acceleration.dotProduct(ground_.getNormal());


		if (projectedAcceleration * time > projectedSpeed)
		{
			Particle* particles[2];
			particles[0] = particles_[i];
			particles[1] = nullptr;

			ParticleContact contact = ParticleContact(particles, 0, 0, ground_.getNormal());
			contacts.push_back(contact);
		}
	}
}
