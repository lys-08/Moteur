#include "ParticleStraightCable.h"

ParticleStraightCable::ParticleStraightCable(Particle* particles[2], double length)
{
	length_ = length;
	particles_[0] = particles[0];
	particles_[1] = particles[1];

}

void ParticleStraightCable::addContact(std::vector<ParticleContact>& contacts, double time)
{
	ParticleContact contact;
	contact.particles[0] = particles_[0];
	contact.particles[1] = particles_[1];
	Vector3d normal = particles_[1]->getPos() - particles_[0]->getPos();
	normal.normalise();

	//nomale et penetration ??
	contact.elasticity = 0;
	contacts.push_back(contact);
}

double ParticleStraightCable::getLength() const
{
	return length_;
}
