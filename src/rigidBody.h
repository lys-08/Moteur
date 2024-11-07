/**
* \file rigidBody.h
* This file contains the declaration of all methods and attributes of the RigidBody class
*/

#pragma once

#include <iostream>
#include "particle.h"
#include "quaternion.h"


class RigidBody
{
private:
    Particle massCenter_; // countain the position
    Quaternion rotation_;
    Vector3d linearVelocity_;
    Vector3d angularVelocity_;

    Vector3d accumForce_;


public:
    // Constructors
    RigidBody(Particle massCenter = Particle(), Quaternion rotation = Quaternion());
    RigidBody(float mass, Vector3d position = Vector3d(0, 0, 0, 1), Quaternion rotation = Quaternion());

    // Getters and Setters
    Particle getMassCenter();
    Quaternion getRotation();
    Vector3d getLinearVelocity();
    Vector3d getAngularVelocity();
    void setRotation(Quaternion rotation);
    void setLinearVelocity(Vector3d linearVelocity);
    void setAngularVelocity(Vector3d angularVelocity);

    // Other methods
    void addForce(const Vector3d& force);
    void addForceAtPoint(const Vector3d& force, const Vector3d& point); // TODO
    void clearAccumForce();
};