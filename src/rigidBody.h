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
    Particle* massCenter_; // countain the position
    Quaternion rotation_;
    Matrix3 rotationMatrix_;
    Vector3d linearVelocity_;
    Vector3d angularVelocity_;
    Matrix3 invJ_;

    Vector3d accumForce_;
    Vector3d accumTorque_;

    Vector3d w_; // width ~ x
    Vector3d h_; // height ~ y
    Vector3d d_; // depth ~ z


public:
    // Constructors
    RigidBody(Particle* massCenter = new Particle(), Quaternion rotation = Quaternion());
    RigidBody(float mass, Vector3d position = Vector3d(0, 0, 0, 1), Vector3d speed = Vector3d(0,0,0,0), Quaternion rotation = Quaternion(), float height = 20, float width = 20, float depth = 20);

    // Getters and Setters
    Particle* getMassCenter();
    Quaternion getRotation();
    Vector3d getLinearVelocity();
    Vector3d getAngularVelocity();
    void setRotation(Quaternion rotation);
    void setLinearVelocity(Vector3d linearVelocity);
    void setAngularVelocity(Vector3d angularVelocity);

    // Other methods
    bool isInRigidBody(const Vector3d& point);
    void addForce(const Vector3d& force);
    void addForceAtPoint(const Vector3d& force, const Vector3d& point);
    void clearAccumForce();
    void clearAccumTorque();
    void integrate(float temps);
};