/**
* \file world.cpp
* This file contains the implementation of all methods and attributes of the World class
*/

#include "world.h"
#include "particleGravity.h"


/**
 * Dummy constructor
 */
World::World()
{
	collisionSphere = new ParticleSphericalCollisionGenerator();
	collisionRest = new ParticleRestCollisionGenerator(ground_);

	friction_ = ParticleFriction(0.1, 0.01);

	springForce = new ParticleSpring();
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

// TODO
/**
 * @brief
 *
 * @return nothing
*/
void World::start(int x,int y)
{
	contactGenerators_.push_back(collisionSphere);
	contactGenerators_.push_back(collisionRest);

	Particle* particleCenter = new Particle(
		Vector3d(x, y, 0, 1),
		Vector3d(0, 0, 0),
		0,
		20
	);

	addParticle(particleCenter);
	originalBlob.push_back(particleCenter);

}

void World::attachNewParticle()
{
	springForce = new ParticleSpring(originalBlob[0], 100, 200);
	Vector3d centerPos = particles_[0]->getPos();
	Particle* particleBlob = new Particle(
		Vector3d(centerPos.getX(), centerPos.getY()- 100, 0, 1),
		Vector3d(0, 0, 0),
		1,
		10
	);

	particleBlob->setSpringForce(particles_[0], 5, 100);
	addParticle(particleBlob);
	originalBlob.push_back(particleBlob);
}

// TODO
/**
 * @brief
 *
 * @return nothing
*/
void World::update(double time)
{
	updateForces(time);
	integrate(time);
	checkForRupture();
	generateContacts();
	solveContacts(time);
	resetAcc();
}

// TODO
/**
 * @brief
 *
 * @param particle
 * @return nothing
*/
void World::addParticle(Particle* particle)
{
	particles_.push_back(particle);
}

void World::addContactGenerator(ParticleContactGenerator* generator)
{
	contactGenerators_.push_back(generator);
}

void World::addSpringForce(ParticleForceGenerator* forceGenerator, Particle* particle)
{
	forcesRegistry_.add(particle, forceGenerator);
}

void World::checkForRupture()
{
	for (int i = 0; i < originalBlob.size(); i++)
	{
		double distance = abs(originalBlob[i]->getPos().distance(originalBlob[0]->getPos()));
		if (distance > 450 && originalBlob[i]->getHasSpring())
		{
			originalBlob[i]->removeSpringForce();
			Particle* particlesCable[2] = { originalBlob[i],originalBlob[0] };
			ParticleCable* collisionCable = new ParticleCable(particlesCable, 200, 0.4);
			addContactGenerator(collisionCable);
		}
	}
	for (int i = 0; i < secondBlob.size(); i++)
	{
		double distance = abs(secondBlob[i]->getPos().distance(secondBlob[0]->getPos()));
		if (distance > 450 && secondBlob[i]->getHasSpring())
		{
			secondBlob[i]->removeSpringForce();
			Particle* particlesCable[2] = { secondBlob[i],secondBlob[0] };
			ParticleCable* collisionCable = new ParticleCable(particlesCable, 200, 0.4);
			addContactGenerator(collisionCable);
		}
	}
}

void World::separateBlob()
{
	if (secondBlob.size() != 0)
	{
		return;
	}

	int sizeNewBlob = particles_.size() / 2;

	originalBlob.erase(originalBlob.begin() + sizeNewBlob, originalBlob.end());

	for (int i = sizeNewBlob; i < particles_.size(); i++)
	{
		particles_[i]->removeSpringForce();
		secondBlob.push_back(particles_[i]);
	}
	for (int i = 1; i < secondBlob.size(); i++)
	{
		secondBlob[i]->setSpringForce(secondBlob[0], 5, 100);
	}
}

void World::reformBlob()
{
	if (secondBlob.empty()) {

		return;
	}

	Particle* centerOriginalBlob = originalBlob[0];

	for (int i = 0; i < secondBlob.size(); i++) 
	{
		secondBlob[i]->removeSpringForce();

		secondBlob[i]->setSpringForce(centerOriginalBlob, 5, 100);


		originalBlob.push_back(secondBlob[i]);
	}

	secondBlob.clear();
}



// TODO
/**
 * @brief
 *
 * @param time
 * @return nothing
*/
void World::updateForces(double time)
{
	for (int i = 0; i < particles_.size(); i++)
	{
		forcesRegistry_.add(particles_[i], &g_);
		forcesRegistry_.add(particles_[i], &friction_);

		if (particles_[i]->getHasSpring())
		{
			forcesRegistry_.add(particles_[i], &particles_[i]->getSpring());
		}
		if (particles_[i]->getHasSetSpring())
		{
			forcesRegistry_.add(particles_[i], &particles_[i]->getSetSpring());
		}
	}
	forcesRegistry_.updateForce(time);
	forcesRegistry_.clear();
}

// TODO
/**
 * @brief
 *
 * @return nothing
*/
void World::generateContacts()
{
	collisionSphere->setParticles(particles_);
	collisionRest->setParticles(particles_);
	for (int i = 0; i < contactGenerators_.size(); i++)
	{
		contactGenerators_[i]->addContact(contacts_, 0);
	}
}

// TODO
/**
 * @brief
 *
 * @param duration
 * @return nothing
*/
void World::solveContacts(double duration)
{
	for (int i = 0; i < contacts_.size(); i++)
	{
		contacts_[i].solve();
	}
	contacts_.clear();
}

// TODO
/**
 * @brief
 *
 * @param time
 * @return nothing
*/
void World::integrate(double time)
{
	/*if (particles_.size() != 0)
	{
		particles_[0]->setPos(Vector3d(500,500,0));
	}*/
	for (int i = 0; i < particles_.size(); i++)
	{
		particles_[i]->integrate(time);
	}
}

// TODO
/**
 * @brief
 *
 * @return nothing
*/
void World::resetAcc()
{
	for (int i = 0; i < particles_.size(); i++)
	{
		particles_[i]->clearAccumForce();
	}
}
