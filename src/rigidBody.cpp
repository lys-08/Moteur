/**
* \file rigidBody.cpp
* This file contains the implementation of all methods and attributes of the RigidBody class
*/

#include "rigidBody.h"





/**
 * @brief Default and evaluated constructor
 */
RigidBody::RigidBody(Particle massCenter, Quaternion orientation)
{
    // TODO
}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

Particle RigidBody::getMassCenter()
{
    return massCenter_;
}

Quaternion RigidBody::getRotation()
{
    return rotation_;
}

void RigidBody::setRotation(Quaternion rotation)
{
    rotation_ = rotation;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================