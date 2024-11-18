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
    massCenter->setRigidBody(this);
    rotation_ = rotation;
    angularVelocity_ = Vector3d();

    // By default : cube with side 2
    w_ = Vector3d(1, 0, 0, 0);
    h_ = Vector3d(0, 1, 0, 0);
    d_ = Vector3d(0, 0, 1, 0);

    double val = (1. / 12) * massCenter_->getMass() * 8; // (h^2 + d^2) = (l^2 + h^2) = (l^2 + d^2) = 4 + 4 = 8

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
    massCenter_ = new Particle(position, speed, 1, mass, this); // TODO typeDraw
    rotation_ = rotation;
    angularVelocity_ = Vector3d();

    w_ = Vector3d(position.getX(), position.getY() + width / 2, position.getZ(), 1) - position;
    h_ = Vector3d(position.getX() + height / 2, position.getY(), position.getZ(), 1) - position;
    d_ = Vector3d(position.getX(), position.getY(), position.getZ() + depth / 2, 1) - position;

    // rectangular cuboid
    invJ_ = Matrix3(
        (1. / 12) * massCenter_->getMass() * (pow(h_.norm(), 2) + pow(d_.norm(), 2)),
        0, 
        0,

        0, 
        (1. / 12)* massCenter_->getMass() * (pow(w_.norm(), 2) + pow(h_.norm(), 2)),
        0,

        0, 
        0, 
        (1. / 12)* massCenter_->getMass() * (pow(w_.norm(), 2) + pow(d_.norm(), 2))
    );
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

bool RigidBody::isInRigidBody(const Vector3d& point)
{
    int x = massCenter_->getPos().getX();
    int y = massCenter_->getPos().getY();
    int z = massCenter_->getPos().getZ();
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

    Vector3d relativePoint = point - massCenter_->getPos();

    bool alignedWithH = (point - massCenter_->getPos()).crossProduct(h_).norm() < 1e-6;
    bool alignedWithW = (point - massCenter_->getPos()).crossProduct(w_).norm() < 1e-6;
    bool alignedWithD = (point - massCenter_->getPos()).crossProduct(d_).norm() < 1e-6;

    if (alignedWithH || alignedWithW || alignedWithD)
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

void RigidBody::clearAccumTorque()
{
    accumTorque_ = Vector3d(0, 0, 0, 0);
}

void RigidBody::integrate(float temps)
{
    massCenter_->integrate(temps);
    angularVelocity_ += (Matrix3xVector(invJ_, accumTorque_) * temps);
    rotation_ += (0.5 * Quaternion(0, angularVelocity_.getX(), angularVelocity_.getY(), angularVelocity_.getZ()) * rotation_ * temps);
    rotationMatrix_ = rotation_.toMatrix();
    invJ_ = rotationMatrix_ * invJ_ * rotationMatrix_.inv();
}

void RigidBody::draw()
{
    ofNoFill();
    massCenter_->draw();

    ofVec3f position = massCenter_->getPos().v3();
    ofMatrix4x4 rotationMatrix = ofMatrix4x4(rotationMatrix_.m4());

    ofPushMatrix();
    ofTranslate(position);
    ofMultMatrix(rotationMatrix);


    float width = w_.norm() * 2;
    float height = h_.norm() * 2;
    float depth = d_.norm() * 2;
    ofDrawBox(0, 0, 0, width, height, depth);

    ofPopMatrix();
    ofFill();
}
