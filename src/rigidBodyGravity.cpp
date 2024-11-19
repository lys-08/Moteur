/**
* \file rigidBodyGravity.cpp
* This file contains the implementation of all methods and attributes of the RigidBodyGravity class
*/

#include "rigidBodyGravity.h"
#include "rigidBody.h"



/**
 * @brief Default and evaluated constructor
 */
RigidBodyGravity::RigidBodyGravity(const Vector3d& g) 
{
    gravity_ = g;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief Update the force for a rigidBody according to the duration
 *
 * @param RigidBody the rigidBody whose force is to be updated
 * @param duration
*/
void RigidBodyGravity::updateForce(RigidBody* rigidBody, float duration)
{
    // We check if the RigidBody has a valid mass (finite)
    if (rigidBody->getMassCenter()->getInvertMass() <= 0.0f) return;

    double mass = 1.0 / rigidBody->getMassCenter()->getInvertMass();
    Vector3d force = gravity_ * mass;
    rigidBody->addForceAtPoint(force, rigidBody->getMassCenter()->getPos());
}
