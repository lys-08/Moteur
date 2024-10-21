#include "particleContact.h"

void ParticleContact::solve() // solve the contact, i.e. apply the forces to the particles
{
	Vector3d relativeVelocity = particles[0]->getSpeed() - particles[1]->getSpeed(); // get the relative velocity between the two particles
	float relativeVelocityNormal = relativeVelocity.dotProduct(normal); // get the relative velocity normal to the contact normal

	double m_v0 = particles[0]->getInvertMass();
	double m_v1 = particles[1]->getInvertMass();

	if (relativeVelocityNormal > 0)
	{
		particles[0]->setPos(particles[0]->getPos() + m_v1 / (m_v1 + m_v0) * interpenetration);
		particles[1]->setPos(particles[1]->getPos() + -m_v0 / (m_v1 + m_v0) * interpenetration);
	}
	else
	{
		particles[0]->setPos(particles[0]->getPos()  + -m_v1 / (m_v1 + m_v0) * interpenetration);
		particles[1]->setPos(particles[1]->getPos() + m_v0 / (m_v1 + m_v0) * interpenetration);
	}

	float impulse = -(1 + elasticity) * relativeVelocityNormal;
	impulse /= m_v0 + m_v1;

	particles[0]->setSpeed(particles[0]->getSpeed() - impulse * m_v0 * normal);
	particles[1]->setSpeed(particles[1]->getSpeed() + impulse * m_v1 * normal);
}