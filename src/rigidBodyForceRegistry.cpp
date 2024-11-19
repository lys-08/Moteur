/**
* \file RigidBodyForceRegistry.cpp
* This file contains the implementation of all methods and attributes of the RigidBodyForceRegistry class
*/

#include "rigidBodyForceRegistry.h"


/**
 * @brief Add a rigidBody to the registry
 *
 * @param rigidBody the rigidBody to add
 * @param registry the registry
 * @return nothing
*/
void RigidBodyForceRegistry::add(RigidBody *rigidBody, RigidBodyForceGenerator * forceGenerator)
{
	registry_.push_back({ rigidBody, forceGenerator });
}

/**
 * @brief Remove a rigidBody from the registry
 *
 * @param rigidBody the rigidBody to remove
 * @param registry the registry
 * @return nothing
*/
void RigidBodyForceRegistry::remove(RigidBody* rigidBody, RigidBodyForceGenerator* forceGenerator) // We travel the registry and remove the RigidBody
{
    for (auto it = registry_.begin(); it != registry_.end(); ) 
    {
        if (it->rigidBody == rigidBody && it->forceGenerator == forceGenerator) 
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
void RigidBodyForceRegistry::clear()
{
    registry_.clear();
}

/**
 * @brief Update the force according to the time
 *
 * @param duration
 * @return nothing
*/
void RigidBodyForceRegistry::updateForce(float duration)
{
	for (const auto& registration : registry_)
    {
        registration.forceGenerator->updateForce(registration.rigidBody, duration);
    }
}