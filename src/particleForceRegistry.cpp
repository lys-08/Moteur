/**
* \file particleForceRegistry.cpp
* This file contains the implementation of all methods and attributes of the ParticleForceRegistry class
*/

#include "particleForceRegistry.h"


/**
 * @brief Add a particle to the registry
 *
 * @param particle the particle to add
 * @param registry the registry
 * @return nothing
*/
void ParticleForceRegistry::add(Particle *particle, ParticleForceGenerator * forceGenerator)
{
	registry_.push_back({ particle, forceGenerator });
}

/**
 * @brief Remove a particle from the registry
 *
 * @param particle the particle to remove
 * @param registry the registry
 * @return nothing
*/
void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* forceGenerator) // We travel the registry and remove the particle
{
    for (auto it = registry_.begin(); it != registry_.end(); ) 
    {
        if (it->particle == particle && it->forceGenerator == forceGenerator) 
        {
            it = registry_.erase(it);
        }
        else 
        {
            ++it;
        }
    }
}

/**
 * @brief Clear the registry
 * 
 * @return nothing
*/
void ParticleForceRegistry::clear()
{
    registry_.clear();
}

/**
 * @brief Update the force according to the time
 *
 * @param duration
 * @return nothing
*/
void ParticleForceRegistry::updateForce(float duration)
{
	for (const auto& registration : registry_)
    {
        registration.forceGenerator->updateForce(registration.particle, duration);
    }
}