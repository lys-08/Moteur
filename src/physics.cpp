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
	width_ = x;
	height_ = y;
	octree = OcTree(Vector3d(x/2.0,y/2.0,0.0),x/2.0,y/2.0,250,2,8);
}

/**
 * @brief remove all objects that are not in the main window
 *
 * @return nothing
*/
void Physics::deleteOutOfBounds()
{
	std::vector<RigidBody*> newObject;
	for (int i = 0; i < objects_.size(); i++)
	{
		if (objects_[i]->getMassCenter()->getPos().getX() > width_ || objects_[i]->getMassCenter()->getPos().getX() < 0 ||
			objects_[i]->getMassCenter()->getPos().getY() > height_ || objects_[i]->getMassCenter()->getPos().getY() < 0 ||
			objects_[i]->getMassCenter()->getPos().getZ() > 250 || objects_[i]->getMassCenter()->getPos().getZ() < -250)
		{
			continue;
		}
		newObject.push_back(objects_[i]);
	}

	objects_ = newObject;
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
	deleteOutOfBounds();
	fillTree();
	updateForces(time);
	integrate(time);
	generateContacts();
	solveContacts(time);
	resetAcc();
}

/**
 * @brief Add a rigidBody to the object list
 *
 * @param object the object to ass
 * @return nothing
*/
void Physics::addRigidBody(RigidBody* object)
{
	objects_.push_back(object);
}

/**
 * @brief Add a simple force
 *
 * @param force the force to add
 * @return nothing
*/
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

		//forcesRegistry_.add(objects_[i], &simpleForces_[i]);
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

/**
 * @brief generate contacts if their is collision in the octree
 *
 * @return nothing
*/
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
