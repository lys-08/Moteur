/**
* \file cone.cpp
* This file contains the implementation of all methods and attributes of the Cone class
*/

#include "cone.h"
#include <of3dGraphics.h>
#include <ofGraphics.h>
#include <cmath>

/**
 * @brief Default and evaluated constructor
 */
Cone::Cone(float radius, float height) : RigidBody() {
    radius_ = radius;
    height_ = height;

    double mass = massCenter_->getMass();

    // Moment of inertia for a cone (base at z=0, apex at z=height)
    double Ixx = (3.0 / 10.0) * mass * pow(radius_, 2);
    double Iyy = Ixx;
    double Izz = (3.0 / 5.0) * mass * pow(radius_, 2);

    invJ_ = Matrix3(
        1 / Ixx, 0, 0,
        0, 1 / Iyy, 0,
        0, 0, 1 / Izz
    );
}

/**
 * @brief Evaluated constructor
 */
Cone::Cone(float mass, Vector3d position, Vector3d speed, Quaternion rotation, float radius, float height)
    : RigidBody(mass, position, speed, rotation) {
    radius_ = radius;
    height_ = height;

    // Moment of inertia for a cone
	double Ixx = mass * ((3.0 / 5.0) * pow(height, 2) + pow(radius, 2) * 3/20 );
    double Iyy = Ixx;
    double Izz = (3.0 / 10.0) * mass * pow(radius_, 2);

    invJ_ = Matrix3(
        1 / Ixx, 0, 0,
        0, 1 / Iyy, 0,
        0, 0, 1 / Izz
    );
}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

float Cone::getRadius() const 
{
    return radius_;
}

float Cone::getHeight() const 
{
    return height_;
}

void Cone::setRadius(float radius) 
{
    radius_ = radius;
}

void Cone::setHeight(float height) 
{
    height_ = height;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief Test if a point is in the Cone
 *
 * @param point the point to test
 * @return true if the point is in the cone, false otherwise
*/
bool Cone::isInRigidBody(const Vector3d& point) 
{
    Vector3d apex = massCenter_->getPos() + Vector3d(0, 0, height_, 1);

    // Check if the point lies inside the cone's volume
    float distanceFromAxis = sqrt(pow(point.getX() - massCenter_->getPos().getX(), 2) +
        pow(point.getY() - massCenter_->getPos().getY(), 2));
    float heightAtPoint = height_ - (point.getZ() - massCenter_->getPos().getZ());
    float maxRadiusAtHeight = (heightAtPoint / height_) * radius_;

    return distanceFromAxis <= maxRadiusAtHeight && point.getZ() <= massCenter_->getPos().getZ() + height_ && point.getZ() >= massCenter_->getPos().getZ();
}

/**
 * @brief Test if a point is colinear with one of the axes of the cone
 *
 * @param point the point to test
 * @return true if the point is colinear to one of the axes, false otherwise
*/
bool Cone::isColinear(const Vector3d& force, const Vector3d& point)
{
    double eps = 1e-6;

    bool alignedWithH = (point - massCenter_->getPos()).crossProduct(height_).norm() < 1e-6;
    bool fAlignedWithH = (force - massCenter_->getPos()).crossProduct(height_).norm() < 1e-6;

    return alignedWithH && fAlignedWithH;
}

std::vector<Vector3d> Cone::getVertex()
{
    //TODO
    return std::vector<Vector3d>();
}

/**
 * @brief Calculate the radius of the bounding sphere of the box
 *
 * @return the radius of the bounding sphere of the box
*/
float Cone::calculateBoundingRadius()
{
    float radiusBase = getRadius();
    float height = getHeight();

    return sqrt(radiusBase * radiusBase + (height / 2) * (height / 2));
}

/**
 * @brief Draw the cone in the scene
 *
 * @return nothing
*/
void Cone::draw() 
{
    ofNoFill();
    massCenter_->draw();

    ofVec3f position = massCenter_->getPos().v3();
    ofMatrix4x4 rotationMatrix = ofMatrix4x4(rotationMatrix_.m4());

    ofPushMatrix();
    ofTranslate(position);
    ofMultMatrix(rotationMatrix);

    // Draw the cone
    ofSetColor(52, 174, 180);
    ofDrawCone(0, 0, 0, radius_ * 2, height_);

    ofPopMatrix();
    ofFill();
}
