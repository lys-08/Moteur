/**
* \file Physics.cpp
* This file contains the implementation of all methods and attributes of the Physics class
*/

#include "Physics.h"
#include "particleGravity.h"


/**
 * Constructor
 */
Physics::Physics()
{
	friction_ = ParticleFriction(0.1, 0.01);
	simpleForce = SimpleForce(Vector3d(10.0, 10.0, 0.0));
	springForce = new ParticleSpring();
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

}

/**
 * @brief update loop of the physic body
 *
 * @param time
 * @return nothing
*/
void Physics::update(double time)
{
	updateForces(time);
	integrate(time);
	resetAcc();
}

void Physics::addRigidBody(RigidBody* object)
{
	objects_.push_back(object);
}

/**
 * @brief add forces to the registry, apply the forces to the particles and clear the registry
 *
 * @param time
 * @return nothing
*/
void Physics::updateForces(double time)
{
	std::cout << "updateForces" << std::endl;
	for (int i = 0; i < objects_.size(); i++)
	{
		forcesRegistry_.add(objects_[i]->getMassCenter(), &g_);
		forcesRegistry_.add(objects_[i]->getMassCenter(), &simpleForce);
		//forcesRegistry_.add(particles_[i], &friction_);
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
