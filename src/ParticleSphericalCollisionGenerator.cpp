/**
* \file particleSphericalCollisionGenerator.cpp
* This file contains the implementation of all methods and attributes of the ParticleSphericalCollisionGenerator class
*/

#include "particleSphericalCollisionGenerator.h"

/**
 * @brief Dummy constructor
 */
ParticleSphericalCollisionGenerator::ParticleSphericalCollisionGenerator()
{

}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

void ParticleSphericalCollisionGenerator::setParticles(std::vector<Particle*> particles)
{
	particles_ = particles;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief generate a contact if two spheres are overlaped
 *
 * @param contacts list of all the contacts
 * @param time
 * @return nothing
*/
void ParticleSphericalCollisionGenerator::addContact(std::vector<ParticleContact>& contacts, double time)
{
	int size = particles_.size();
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			double distance = particles_[i]->getPos().distance(particles_[j]->getPos());
			double sumRadius = particles_[i]->getRadius() + particles_[j]->getRadius();
			if (distance < sumRadius)
			{
				Particle* particles[2];
				particles[0] = particles_[i];
				particles[1] = particles_[j];

				float interpenetration = distance - sumRadius;
				Vector3d normal = (particles_[i]->getPos() - particles_[j]->getPos()).normalise2();

				ParticleContact contact = ParticleContact(particles, 1, interpenetration, normal);
				contacts.push_back(contact);
			}
		}
	}
}
