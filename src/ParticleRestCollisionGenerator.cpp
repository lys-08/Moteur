#include "ParticleRestCollisionGenerator.h"

ParticleRestCollisionGenerator::ParticleRestCollisionGenerator()
{

}

void ParticleRestCollisionGenerator::addContact(std::vector<ParticleContact>& contacts, double time)
{
	int size = particles.size();
	for (int i = 0; i < size; i++)
	{
		//projeter sur la normale avant de comparer
		//faire un sol ?
		if ((particles[i]->getForceAccum() * time).norm() > particles[i]->getSpeed().norm())
		{
			ParticleContact contact;
			contact.particles[0] = particles[i];
			contact.particles[1] = nullptr;

			//contact.interpenetration = distance - sumRadius;
			contact.elasticity = 0;

			contacts.push_back(contact);
		}
	}
}
