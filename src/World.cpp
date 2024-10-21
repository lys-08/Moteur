#include "World.h"
#include "particleGravity.h"

World::World()
{
	collisionSphere = &ParticleSphericalCollisionGenerator();
}

void World::start()
{
	contactGenerators_.push_back(collisionSphere);
}

void World::update(double time)
{
	updateForces(time);
	integrate(time);
	generateContacts();
	solveContacts(time);
	resetAcc();
}

void World::addParticle(Particle* particle)
{
	particles_.push_back(particle);
}

void World::updateForces(double time)
{
	for (int i = 0; i < particles_.size(); i++)
	{
		forcesRegistry_.add(particles_[i], &g_);
	}
	forcesRegistry_.updateForce(time);
	forcesRegistry_.clear();
}

void World::generateContacts()
{
	collisionSphere->particles = particles_;
	for (int i = 0; i < contactGenerators_.size(); i++)
	{
		contactGenerators_[i]->addContact(contacts_, 0);
	}
}

void World::solveContacts(double duration)
{
	for (int i = 0; i < contacts_.size(); i++)
	{
		contacts_[i].solve();
	}
	contacts_.clear();
}

void World::integrate(double time)
{
	for (int i = 0; i < particles_.size(); i++)
	{
		particles_[i]->integrate(time);
	}
}

void World::resetAcc()
{
	for (int i = 0; i < particles_.size(); i++)
	{
		particles_[i]->clearAccumForce();
	}
}
