#include "ParticleCable.h"

ParticleCable::ParticleCable(Particle* particles[2], double maxLength)
{
	maxLength_ = maxLength;
	particles_[0] = particles[0];
	particles_[1] = particles[1];
}

void ParticleCable::addContact(std::vector<ParticleContact>& contacts, double time)
{
	if (getActualLength() > maxLength_)
	{
		ParticleContact contact;
		contact.particles[0] = particles_[0];
		contact.particles[1] = particles_[1];
		contact.normal = (particles_[1]->getPos() - particles_[0]->getPos()).normalise2();

		//interpenetration?
		contact.elasticity = elasticity_;
		contacts.push_back(contact);
	}
}

double ParticleCable::getActualLength() const
{
	return (particles_[0]->getPos() - particles_[1]->getPos()).norm();
}
