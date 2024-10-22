/**
* \file particleStraightCable.cpp
* This file contains the implementation of all methods and attributes of the ParticleStraightCable class
*/

#include "ParticleStraightCable.h"


/**
 * @brief Evaluated constructor
 */
ParticleStraightCable::ParticleStraightCable(Particle* particles[2], double length)
{
	length_ = length;
	particles_[0] = particles[0];
	particles_[1] = particles[1];

}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

double ParticleStraightCable::getActualLength() const
{
	return (particles_[0]->getPos() - particles_[1]->getPos()).norm();
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
void ParticleStraightCable::addContact(std::vector<ParticleContact>& contacts, double time)
{
	double actualLength = getActualLength();
	std::cout << "Actual Length: " << actualLength << " | Target Length: " << length_ << std::endl;

	if (abs(actualLength - length_) < 1e-6)
	{
		return;
	}

	Particle* particles[2];
	particles[0] = particles_[0];
	particles[1] = particles_[1];

	double interpenetration = abs(actualLength - length_); //todo
	Vector3d normal = (particles_[1]->getPos() - particles_[0]->getPos()).normalise2();

	if (actualLength > length_)
	{
		normal = -1 * normal;
	}

	ParticleContact contact = ParticleContact(particles, 0, 0, normal);
	contacts.push_back(contact);
}



