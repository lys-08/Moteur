#include "World.h"

void World::update(double time)
{
	updateForces(time);
	integrate(time);
	std::vector<ParticleContact>& contacts = generateContacts();
	solveContacts(contacts, time);
	resetAcc();
}

void World::addParticle(Particle* particle)
{
}

void World::updateForces(double time)
{

}

std::vector<ParticleContact>& World::generateContacts()
{
	return std::vector<ParticleContact>();
}

void World::solveContacts(std::vector<ParticleContact>& contacts, double duration)
{
}

void World::integrate(double time)
{
}

void World::resetAcc()
{
}
