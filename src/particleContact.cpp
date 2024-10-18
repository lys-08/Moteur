#include "particleContact.h"

void ParticleContact::solve()
{
	Vector3d relativeVelocity = particles[0]->getSpeed() - particles[1]->getSpeed();
	float relativeVelocityNormal = relativeVelocity.dotProduct(normal);

	if (relativeVelocityNormal > 0)
	{
		particles[0]->setPos(particles[1]->getInvertMass() / (particles[1]->getInvertMass() + particles[0]->getInvertMass()) * interpenetration);
		particles[1]->setPos(-particles[0]->getInvertMass() / (particles[1]->getInvertMass() + particles[0]->getInvertMass()) * interpenetration);
	}
	else
	{
		particles[0]->setPos(-particles[1]->getInvertMass() / (particles[1]->getInvertMass() + particles[0]->getInvertMass()) * interpenetration);
		particles[1]->setPos(particles[0]->getInvertMass() / (particles[1]->getInvertMass() + particles[0]->getInvertMass()) * interpenetration);
	}

	float impulse = -(1 + elasticity) * relativeVelocityNormal;
	impulse /= particles[0]->getInvertMass() + particles[1]->getInvertMass();
}