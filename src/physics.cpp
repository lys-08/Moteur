/**
* \file Physics.cpp
* This file contains the implementation of all methods and attributes of the Physics class
*/

#include "Physics.h"
#include "rigidBodyGravity.h"


/**
 * Dummy Constructor
 */
Physics::Physics()
{
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief initialize the first particle and the global contact generators
 *
 * @param x,y coordinates of mouse cursor
 * @return nothing
*/
void Physics::start(int x, int y)
{
	octree = OcTree(Vector3d(x/2,y/2,0),x,y,500,2,8);
}

/**
 * @brief fill the octree with existing rigidbodies
 *
 * @return nothing
*/
void Physics::fillTree()
{
	octree.clearOctree();
	for (int i = 0; i < objects_.size(); i++)
	{
		octree.insertRigidBody(objects_[i]);
	}
}

/**
 * @brief update loop of the physic body
 *
 * @param time
 * @return nothing
*/
void Physics::update(double time)
{
	fillTree();
	updateForces(time);
	integrate(time);
	generateContacts();
	solveContacts(time);
	resetAcc();
}

void Physics::addRigidBody(RigidBody* object)
{
	objects_.push_back(object);
}

void Physics::addSimpleForce(SimpleForce force)
{
	simpleForces_.push_back(force);
}

/**
 * @brief add forces to the registry, apply the forces to the particles and clear the registry
 *
 * @param time
 * @return nothing
*/
void Physics::updateForces(double time)
{
	for (int i = 0; i < objects_.size(); i++)
	{
		forcesRegistry_.add(objects_[i], &g_);

		forcesRegistry_.add(objects_[i], &simpleForces_[i]);
	}
	forcesRegistry_.updateForce(time);
	forcesRegistry_.clear();
}

/**
 * @brief integrate the particles using the euler method
 *
 * @param time
 * @return nothing
*/
void Physics::integrate(double time)
{
	for (int i = 0; i < objects_.size(); i++)
	{
		objects_[i]->integrate(time);
	}
}

void Physics::generateContacts()
{
	octree.checkCollisionsInTree(contacts_);
}

/**
 * @brief solve contacts using the impulse method
 *
 * @param duration
 * @return nothing
*/
void Physics::solveContacts(double duration)
{
	for (int i = 0; i < contacts_.size(); i++)
	{
		contacts_[i].solve();
	}
	contacts_.clear();
}

/**
 * @brief reset accumulator for the particles
 *
 * @return nothing
*/
void Physics::resetAcc()
{
	for (int i = 0; i < objects_.size(); i++)
	{
		objects_[i]->clearAccumForce();
		objects_[i]->clearAccumTorque();
	}
}
