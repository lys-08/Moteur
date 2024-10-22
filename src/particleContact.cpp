#include "particleContact.h"


ParticleContact::ParticleContact(Particle* particles[2], float elasticity, float interpenetration, Vector3d normal)
{
	particles_[0] = particles[0];
	particles_[1] = particles[1];

	elasticity_ = elasticity;
	interpenetration_ = interpenetration;
	normal_ = normal;
}

void ParticleContact::solve() // solve the contact, i.e. apply the forces to the particles
{
	Vector3d relativeVelocity = particles_[0]->getSpeed() - particles_[1]->getSpeed(); // get the relative velocity between the two particles
	float relativeVelocityNormal = relativeVelocity.dotProduct(normal_); // get the relative velocity normal to the contact normal

	double m_v0 = particles_[0]->getInvertMass();
	double m_v1 = particles_[1]->getInvertMass();

	if (relativeVelocityNormal > 0)
	{
		particles_[0]->setPos(particles_[0]->getPos() + m_v1 / (m_v1 + m_v0) * interpenetration_);
		particles_[1]->setPos(particles_[1]->getPos() + -m_v0 / (m_v1 + m_v0) * interpenetration_);
	}
	else
	{
		particles_[0]->setPos(particles_[0]->getPos()  + -m_v1 / (m_v1 + m_v0) * interpenetration_);
		particles_[1]->setPos(particles_[1]->getPos() + m_v0 / (m_v1 + m_v0) * interpenetration_);
	}

	float impulse = -(1 + elasticity_) * relativeVelocityNormal;
	impulse /= m_v0 + m_v1;

	particles_[0]->setSpeed(particles_[0]->getSpeed() - impulse * m_v0 * normal_);
	particles_[1]->setSpeed(particles_[1]->getSpeed() + impulse * m_v1 * normal_);
}