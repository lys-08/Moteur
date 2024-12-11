/**
* \file rigidBody.cpp
* This file contains the implementation of all methods and attributes of the RigidBody class
*/

#include "rigidBody.h"
#include <of3dGraphics.h>
#include <ofGraphics.h>




/**
 * @brief Default and evaluated constructor
 */
RigidBody::RigidBody(Particle* massCenter, Quaternion rotation)
{
    massCenter_ = massCenter;
    rotation_ = rotation;
    angularVelocity_ = Vector3d();
}

/**
 * @brief Evaluated constructor
 */
RigidBody::RigidBody(float mass, Vector3d position, Vector3d speed, Quaternion rotation)
{
    massCenter_ = new Particle(position, speed, 1, mass);
    rotation_ = rotation;
    angularVelocity_ = Vector3d();
}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

Particle* RigidBody::getMassCenter()
{
    return massCenter_;
}

Quaternion RigidBody::getRotation()
{
    return rotation_;
}

Vector3d RigidBody::getAngularVelocity()
{
    return angularVelocity_;
}

Matrix3 RigidBody::getInvJ() const
{
    return invJ_;
}

void RigidBody::setRotation(Quaternion rotation)
{
    rotation_ = rotation;
}

void RigidBody::setAngularVelocity(Vector3d angularVelocity)
{
    angularVelocity_ = angularVelocity;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief add a force apply to the center of mass to the accumulator
 *
 * @param force the force to add to accumForce_
 * @return nothing
*/
void RigidBody::addForce(const Vector3d& force)
{
    addForceAtPoint(force, massCenter_->getPos());
}

/**
 * @brief add a force apply to a specific point to the accumulator
 *
 * @param force the force to add to accumForce_
 * @param point the application point of the force
 * @return nothing
*/
void RigidBody::addForceAtPoint(const Vector3d& force, const Vector3d& point)
{
    if (!isInRigidBody(point)) return;

    if (this->isColinear(force,point))
    {
        massCenter_->addForce(force);
    }
    else
    {
        accumTorque_ += (point - massCenter_->getPos()).crossProduct(force);
        massCenter_->addForce(force);
    }
}


/**
 * @brief Clear accumForce
 *
 * @return nothing
*/
void RigidBody::clearAccumForce()
{
    massCenter_->clearAccumForce();
    accumForce_ = Vector3d(0, 0, 0, 0);
}

/**
 * @brief Clear accumTorque
 *
 * @return nothing
*/
void RigidBody::clearAccumTorque()
{
    accumTorque_ = Vector3d(0, 0, 0, 0);
}

/**
 * @brief Integrates the position and rotation of the rigid body through time
 *
 * @param time
 * @return nothing
*/
void RigidBody::integrate(float temps)
{
    massCenter_->integrate(temps);
    angularVelocity_ += (Matrix3xVector(invJ_, accumTorque_) * temps);
    angularVelocity_.normalise();
    rotation_ += (0.5 * Quaternion(0, angularVelocity_.getX(), angularVelocity_.getY(), angularVelocity_.getZ()) * rotation_ * temps);
    rotationMatrix_ = rotation_.toMatrix();
    invJ_ = rotationMatrix_ * invJ_ * rotationMatrix_.inv();
}