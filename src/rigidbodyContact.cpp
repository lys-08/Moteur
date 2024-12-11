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
	normal_ = normal;
	contactPoint_ = contactPoint;
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
	double inv_m0 = rigidBodies_[0]->getMassCenter()->getInvertMass();
	double m0 = 1 / inv_m0;

	if (rigidBodies_[1] != nullptr)
	{
		// Relative speed at the point of contact
		Vector3d relativeVelocity = rigidBodies_[0]->getMassCenter()->getSpeed() - rigidBodies_[1]->getMassCenter()->getSpeed();
		float relativeVelocityNormal = relativeVelocity.dotProduct(normal_);

		double inv_m1 = rigidBodies_[1]->getMassCenter()->getInvertMass();
		double m1 = 1 / inv_m1;

		if (relativeVelocityNormal > 0)
		{
			rigidBodies_[0]->getMassCenter()->setPos(rigidBodies_[0]->getMassCenter()->getPos() + (m1 / (m1 + m0)) * interpenetration_ * normal_);
			rigidBodies_[1]->getMassCenter()->setPos(rigidBodies_[1]->getMassCenter()->getPos() + (-m0 / (m1 + m0)) * interpenetration_ * normal_);
		}
		else
		{
			rigidBodies_[0]->getMassCenter()->setPos(rigidBodies_[0]->getMassCenter()->getPos() + (-m1 / (m1 + m0)) * interpenetration_ * normal_);
			rigidBodies_[1]->getMassCenter()->setPos(rigidBodies_[1]->getMassCenter()->getPos() + (m0 / (m1 + m0)) * interpenetration_ * normal_);
		}

		// Collision pulse calculation
		float impulse = (1 + elasticity_) * relativeVelocityNormal;
		impulse /= (inv_m0 + inv_m1) * normal_.dotProduct(normal_);

		// Update linear velocity
		rigidBodies_[0]->getMassCenter()->setSpeed(rigidBodies_[0]->getMassCenter()->getSpeed() - impulse * inv_m0 * normal_);
		rigidBodies_[1]->getMassCenter()->setSpeed(rigidBodies_[1]->getMassCenter()->getSpeed() + impulse * inv_m1 * normal_);

		// Update angular velocity
		Vector3d contactOffset0 = contactPoint_ - rigidBodies_[0]->getMassCenter()->getPos();
		Vector3d contactOffset1 = contactPoint_ - rigidBodies_[1]->getMassCenter()->getPos();

		Vector3d angularVelocity0 = rigidBodies_[0]->getAngularVelocity() + Matrix3xVector(rigidBodies_[0]->getInvJ(), contactOffset0.crossProduct(impulse * normal_));
		rigidBodies_[0]->setAngularVelocity(angularVelocity0);
		Vector3d angularVelocity1 = rigidBodies_[1]->getAngularVelocity() + Matrix3xVector(rigidBodies_[1]->getInvJ(), contactOffset1.crossProduct(impulse * normal_));
		rigidBodies_[0]->setAngularVelocity(angularVelocity0);
	}
	else // Only one rigidBody
	{
		rigidBodies_[0]->getMassCenter()->setPos(rigidBodies_[0]->getMassCenter()->getPos() - interpenetration_ * normal_);
		double impulse = rigidBodies_[0]->getMassCenter()->getSpeed().dotProduct(normal_) / (inv_m0 * normal_.dotProduct(normal_));
		rigidBodies_[0]->getMassCenter()->setSpeed(rigidBodies_[0]->getMassCenter()->getSpeed() - impulse * inv_m0 * normal_);

		Vector3d contactOffset = contactPoint_ - rigidBodies_[0]->getMassCenter()->getPos();
		Vector3d angularVelocity = rigidBodies_[0]->getAngularVelocity() + Matrix3xVector(rigidBodies_[0]->getInvJ(), contactOffset.crossProduct(impulse * normal_));
		rigidBodies_[0]->setAngularVelocity(angularVelocity);
	}
}