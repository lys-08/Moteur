#include "World.h"
#include "particleGravity.h"

/**
 * Dummy constructor
 */
World::World()
{
	collisionSphere = new ParticleSphericalCollisionGenerator();
	collisionRest = new ParticleRestCollisionGenerator(ground_);
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
