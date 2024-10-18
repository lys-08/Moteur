#include "ParticleSphericalCollisionGenerator.h"

ParticleSphericalCollisionGenerator::ParticleSphericalCollisionGenerator()
{

}

void ParticleSphericalCollisionGenerator::addContact(std::vector<ParticleContact>& contacts, double time)
{
	int size = particles.size();
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			double distance = particles[i]->getPos().distance(particles[j]->getPos());
			double sumRadius = particles[i]->getRadius() + particles[j]->getRadius();
			if (distance < sumRadius)
			{
				ParticleContact contact;
				contact.particles[0] = particles[i];
				contact.particles[1] = particles[j];

				contact.elasticity = 1;
				contact.interpenetration = distance - sumRadius;
				contact.normal = (particles[i]->getPos() - particles[j]->getPos()).normalise2();

				contacts.push_back(contact);
			}
		}
	}
}
