/**
* \file box.cpp
* This file contains the implementation of all methods and attributes of the Box class
*/

#include "box.h"
#include <of3dGraphics.h>
#include <ofGraphics.h>




/**
 * @brief Default and evaluated constructor
 */
Box::Box(float height, float width, float depth) : RigidBody()
{
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
Box::Box(float mass, Vector3d position, Vector3d speed, Quaternion rotation, float height, float width, float depth) : 
    RigidBody(mass, position, speed, rotation)
{
    w_ = Vector3d(position.getX(), position.getY() + width / 2, position.getZ(), 1) - position;
    h_ = Vector3d(position.getX() + height / 2, position.getY(), position.getZ(), 1) - position;
    d_ = Vector3d(position.getX(), position.getY(), position.getZ() + depth / 2, 1) - position;

    invJ_ = Matrix3(
        (1. / 12) * massCenter_->getMass() * (pow(h_.norm(), 2) + pow(d_.norm(), 2)),
        0,
        0,

        0,
        (1. / 12) * massCenter_->getMass() * (pow(w_.norm(), 2) + pow(h_.norm(), 2)),
        0,

        0,
        0,
        (1. / 12) * massCenter_->getMass() * (pow(w_.norm(), 2) + pow(d_.norm(), 2))
    );
}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

Vector3d Box::getW()
{
    return w_;
}

Vector3d Box::getH()
{
    return h_;
}

Vector3d Box::getD()
{
    return d_;
}

void Box::setW(Vector3d w)
{
    w_ = w;
}

void Box::setH(Vector3d h)
{
    h_ = h;
}

void Box::setD(Vector3d d)
{
    d_ = d;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief Test if a point is in the Box
 *
 * @param point the point to test
 * @return true if the point is in the box, false otherwise
*/
bool Box::isInRigidBody(const Vector3d& point)
{
    int x = massCenter_->getPos().getX();
    int y = massCenter_->getPos().getY();
    int z = massCenter_->getPos().getZ();
    return (point.getX() <= x + w_.norm() || point.getX() >= x - w_.norm())
        && (point.getY() <= y + h_.norm() || point.getY() >= y - h_.norm())
        && (point.getZ() <= z + d_.norm() || point.getZ() >= z - d_.norm());
}

/**
 * @brief Test if a point is colinear with one of the axes of the box
 *
 * @param point the point to test
 * @return true if the point is colinear to one of the axes, false otherwise
*/
bool Box::isColinear(const Vector3d& force, const Vector3d& point)
{
    double eps = 1e-6;

    bool alignedWithH = (point - massCenter_->getPos()).crossProduct(h_).norm() < 1e-6;
    bool alignedWithW = (point - massCenter_->getPos()).crossProduct(w_).norm() < 1e-6;
    bool alignedWithD = (point - massCenter_->getPos()).crossProduct(d_).norm() < 1e-6;

    bool fAlignedWithH = (force - massCenter_->getPos()).crossProduct(h_).norm() < 1e-6;
    bool fAlignedWithW = (force - massCenter_->getPos()).crossProduct(w_).norm() < 1e-6;
    bool fAlignedWithD = (force - massCenter_->getPos()).crossProduct(d_).norm() < 1e-6;

    return (alignedWithH && fAlignedWithH) || (alignedWithW && fAlignedWithW) || (alignedWithD && fAlignedWithD);
}

std::vector<Vector3d> Box::getVertex()
{
    Vector3d v1 = Vector3d(w_ + h_ + d_);
    Vector3d v2 = Vector3d(w_ + h_ - d_);
    Vector3d v3 = Vector3d(w_ + d_ - h_);
    Vector3d v4 = Vector3d(w_ - d_ - h_);
    Vector3d v5 = Vector3d(h_ + d_ - w_);
    Vector3d v6 = Vector3d(h_ - d_ - w_);
    Vector3d v7 = Vector3d(d_ - h_ - w_);
    Vector3d v8 = Vector3d(-1 * d_ - h_ - w_);
    return std::vector<Vector3d>({ v1,v2,v3,v4,v5,v6,v7,v8 });
}

/**
 * @brief Calculate the radius of the bounding sphere of the box
 *
 * @return the radius of the bounding sphere of the box
*/
float Box::calculateBoundingRadius()
{
    return getH().norm() * 1.3;
}


/**
 * @brief Draw the box in the scene
 *
 * @return nothing
*/
void Box::draw()
{
    ofNoFill();
    massCenter_->draw();

    ofVec3f position = massCenter_->getPos().v3();
    ofMatrix4x4 rotationMatrix = ofMatrix4x4(rotationMatrix_.m4());

    // Apply location
    ofPushMatrix();
    ofTranslate(position);
    ofMultMatrix(rotationMatrix);

    // Draw the box
    float width = w_.norm() * 2;
    float height = h_.norm() * 2;
    float depth = d_.norm() * 2;
    ofSetColor(52, 174, 180);
    ofDrawBox(0, 0, 0, width, height, depth);
    //ofDrawSphere(calculateBoundingRadius());

    ofPopMatrix();
    ofFill();
}