/**
* \file rigidbodyContact.cpp
* This file contains the implementation of all methods and attributes of the RigidBodyContact class
*/

#include "rigidbodyContact.h"

/**
 * @brief Evaluated constructor
 */
RigidBodyContact::RigidBodyContact(RigidBody* rigidBodies[2], float elasticity, float interpenetration, Vector3d contactPoint, Vector3d normal)
{
	rigidBodies_[0] = rigidBodies[0];
	rigidBodies_[1] = rigidBodies[1];

	elasticity_ = elasticity;
	interpenetration_ = interpenetration;
	contactPoint_ = contactPoint;
	normal_ = normal;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief resolve collisions based on impulsion and interpenetration method
 *
 * @return nothing
*/
void RigidBodyContact::solve()
{
	// TODO
	/*double m_v0 = particles_[0]->getInvertMass();
	double m0 = 1 / m_v0;

	if (particles_[1] != nullptr)
	{
		Vector3d relativeVelocity = particles_[0]->getSpeed() - particles_[1]->getSpeed();
		float relativeVelocityNormal = relativeVelocity.dotProduct(normal_);

		double m_v1 = particles_[1]->getInvertMass();
		double m1 = 1 / m_v1;

		if (relativeVelocityNormal > 0)
		{
			particles_[0]->setPos(particles_[0]->getPos() + (m1 / (m1 + m0)) * interpenetration_ * normal_);
			particles_[1]->setPos(particles_[1]->getPos() + (- m0 / (m1 + m0)) * interpenetration_ * normal_);
		}
		else
		{
			particles_[0]->setPos(particles_[0]->getPos()  + (- m1 / (m1 + m0)) * interpenetration_ * normal_);
			particles_[1]->setPos(particles_[1]->getPos() + (m0 / (m1 + m0)) * interpenetration_ * normal_);
		}

		float impulse = (1 + elasticity_) * relativeVelocityNormal;
		impulse /= (m_v0 + m_v1) * normal_.dotProduct(normal_);

		particles_[0]->setSpeed(particles_[0]->getSpeed() - impulse * m_v0 * normal_);
		particles_[1]->setSpeed(particles_[1]->getSpeed() + impulse * m_v1 * normal_);
	}
	else
	{
		particles_[0]->setPos(particles_[0]->getPos() - interpenetration_ * normal_);
		double impulse = particles_[0]->getSpeed().dotProduct(normal_) / (m_v0 * normal_.dotProduct(normal_));
		particles_[0]->setSpeed(particles_[0]->getSpeed() - impulse * m_v0 * normal_);
	}*/
}