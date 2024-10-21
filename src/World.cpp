#include "World.h"

void World::update(double time)
{
	updateForces(time);
	integrate(time);
	std::vector<ParticleContact>& contacts = generateContacts();
	solveContacts(contacts, time);
	resetAcc();+
}
