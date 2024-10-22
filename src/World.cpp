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

	fk_ = ParticleKineticFriction(0.3, ground_);
	fs_ = ParticleStaticFriction(0.3,ground_);

	setSpringForce = new ParticleSetSpring(Vector3d(200, 900, 0, 1), 100, 200);
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
void World::start()
{
	contactGenerators_.push_back(collisionSphere);
	contactGenerators_.push_back(collisionRest);
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
	generateContacts();
	//std::cout << contacts_.size() << std::endl;
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
		forcesRegistry_.add(particles_[i], &fk_);
		//forcesRegistry_.add(particles_[i], &fs_);
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
