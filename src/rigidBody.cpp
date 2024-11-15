/**
* \file rigidBody.cpp
* This file contains the implementation of all methods and attributes of the RigidBody class
*/

#include "rigidBody.h"





/**
 * @brief Default and evaluated constructor
 */
RigidBody::RigidBody(Particle massCenter, Quaternion rotation)
{
    massCenter_ = massCenter;
    rotation_ = rotation;
    linearVelocity_ = Vector3d();
    angularVelocity_ = Vector3d();

    // By default : cube with side 2
    w_ = Vector3d(1, 0, 0, 0);
    h_ = Vector3d(0, 1, 0, 0);
    d_ = Vector3d(0, 0, 1, 0);

    double val = (1. / 12) * massCenter_.getMass() * 8; // (h^2 + d^2) = (l^2 + h^2) = (l^2 + d^2) = 4 + 4 = 8

    invJ_ = Matrix3(
        val, 0, 0,
        0, val, 0,
        0, 0, val
    );
}

/**
 * @brief Evaluated constructor
 */
RigidBody::RigidBody(float mass, Vector3d position, Vector3d speed, Quaternion rotation, float height, float width, float depth)
{
    massCenter_ = Particle(position, speed, 1, mass); // TODO typeDraw
    rotation_ = rotation;
    linearVelocity_ = Vector3d();
    angularVelocity_ = Vector3d();

    w_ = Vector3d(position.getX(), position.getY() + width / 2, position.getZ(), 1) - position;
    h_ = Vector3d(position.getX() + height / 2, position.getY(), position.getZ(), 1) - position;
    d_ = Vector3d(position.getX(), position.getY(), position.getZ() + depth / 2, 1) - position;

    // rectangular cuboid
    invJ_ = Matrix3(
        (1. / 12) * massCenter_.getMass() * (pow(h_.norm(), 2) + pow(d_.norm(), 2)),
        0, 
        0,

        0, 
        (1. / 12)* massCenter_.getMass() * (pow(w_.norm(), 2) + pow(h_.norm(), 2)),
        0,

        0, 
        0, 
        (1. / 12)* massCenter_.getMass() * (pow(w_.norm(), 2) + pow(d_.norm(), 2))
    );
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

Vector3d RigidBody::getLinearVelocity()
{
    return linearVelocity_;
}

Vector3d RigidBody::getAngularVelocity()
{
    return angularVelocity_;
}

void RigidBody::setRotation(Quaternion rotation)
{
    rotation_ = rotation;
}

void RigidBody::setLinearVelocity(Vector3d linearVelocity)
{
    linearVelocity_ = linearVelocity;
}

void RigidBody::setAngularVelocity(Vector3d angularVelocity)
{
    angularVelocity_ = angularVelocity;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

bool RigidBody::isInRigidBody(const Vector3d& point)
{
    int x = massCenter_.getPos().getX();
    int y = massCenter_.getPos().getY();
    int z = massCenter_.getPos().getZ();
    return (point.getX() <= x + w_.norm() || point.getX() >= x - w_.norm()) 
        && (point.getY() <= y + h_.norm() || point.getY() >= y - h_.norm()) 
        && (point.getZ() <= z + d_.norm() || point.getZ() >= z - d_.norm());
}

/**
 * @brief add a force apply to the center of mass to the accumulator
 *
 * @param force the force to add to accumForce_
 * @return nothing
*/
void RigidBody::addForce(const Vector3d& force)
{
    addForceAtPoint(force, massCenter_.getPos());
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

    if (h_.crossProduct(point).norm() == 0 || w_.crossProduct(point).norm() == 0 || d_.crossProduct(point).norm() == 0)
    {
        massCenter_.addForce(force);
    }
    else
    {
        accumTorque_ += (point.distance(massCenter_.getPos()) * force);
        accumForce_ += force;
    }
}

/**
 * @brief Clear accumForce
 *
 * @return nothing
*/
void RigidBody::clearAccumForce()
{
    accumForce_ = Vector3d(0, 0, 0, 0);
}

void RigidBody::clearAccumTorque()
{
    accumTorque_ = Vector3d(0, 0, 0, 0);
}

void RigidBody::integrate(float temps)
{
    massCenter_.integrate(temps);
    linearVelocity_ += (accumForce_ * temps);
    angularVelocity_ += (Matrix3xVector(invJ_, accumForce_) * temps);
    rotation_ += (0.5 * Quaternion(0, angularVelocity_.getX(), angularVelocity_.getY(), angularVelocity_.getZ()) * rotation_ * temps);
    rotationMatrix_ = rotation_.toMatrix();
    invJ_ = rotationMatrix_ * invJ_ * rotationMatrix_.inv();
}
