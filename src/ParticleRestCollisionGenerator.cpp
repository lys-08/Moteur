#include "ParticleRestCollisionGenerator.h"

ParticleRestCollisionGenerator::ParticleRestCollisionGenerator(Plane ground)
{
	ground_ = ground;
}

void ParticleRestCollisionGenerator::addContact(std::vector<ParticleContact>& contacts, double time)
{
	int size = particles.size();
	for (int i = 0; i < size; i++)
	{
		double projectedSpeed = particles[i]->getSpeed().dotProduct(ground_.getNormal());
		Vector3d acceleration = particles[i]->getForceAccum() * particles[i]->getInvertMass();
		double projectedAcceleration = acceleration.dotProduct(ground_.getNormal());


		if (projectedAcceleration * time > projectedSpeed)
		{
			ParticleContact contact;
			contact.particles[0] = particles[i];
			contact.particles[1] = nullptr;

			contact.normal = ground_.getNormal();
			contact.interpenetration = 0;
			contact.elasticity = 0;

			contacts.push_back(contact);
		}
	}
}
