#include "ParticleStraightCable.h"

ParticleStraightCable::ParticleStraightCable(Particle* particles[2], double length)
{
	length_ = length;
	particles_[0] = particles[0];
	particles_[1] = particles[1];

}

void ParticleStraightCable::addContact(std::vector<ParticleContact>& contacts, double time)
{
	if (getActualLength() > length_)
	{
		ParticleContact contact;
		contact.particles[0] = particles_[0];
		contact.particles[1] = particles_[1];

		contact.normal = (particles_[1]->getPos() - particles_[0]->getPos()).normalise2();
		int direction = getActualLength() > length_ ? 1 : -1;
		contact.normal *= direction;
		contact.interpenetration = direction * (getActualLength() - length_);
		contact.elasticity = 0;

		contacts.push_back(contact);
	}
}

double ParticleStraightCable::getActualLength() const
{
	return (particles_[0]->getPos() - particles_[1]->getPos()).norm();
}
