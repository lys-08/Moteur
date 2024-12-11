/**
* \file rigidBody.h
* This file contains the declaration of all methods and attributes of the RigidBody class
*/

#pragma once

#include <iostream>
#include "quaternion.h"
#include "particle.h"

class RigidBody
{
protected:
    Particle* massCenter_; // contain the position
    Quaternion rotation_;
    Matrix3 rotationMatrix_;
    Vector3d angularVelocity_;
    Matrix3 invJ_;

    Vector3d accumForce_;
    Vector3d accumTorque_;

public:
    // Constructors
    RigidBody(Particle* massCenter = nullptr, Quaternion rotation = Quaternion());
    RigidBody(float mass, Vector3d position = Vector3d(0, 0, 0, 1), Vector3d speed = Vector3d(0,0,0,0), Quaternion rotation = Quaternion());

    // Getters and Setters
    Particle* getMassCenter();
    Quaternion getRotation();
    Vector3d getAngularVelocity();
    Matrix3 getInvJ() const;
    void setRotation(Quaternion rotation);
    void setAngularVelocity(Vector3d angularVelocity);

    // Other methods
    virtual bool isInRigidBody(const Vector3d& point) = 0;
    virtual bool isColinear(const Vector3d& force, const Vector3d& point) = 0;
    virtual std::vector<Vector3d> getVertex() = 0;
    void addForce(const Vector3d& force);
    void addForceAtPoint(const Vector3d& force, const Vector3d& point);
    void clearAccumForce();
    void clearAccumTorque();
    void integrate(float temps);
    virtual void draw() = 0;

	// Bounding Volume
    virtual float calculateBoundingRadius() = 0;
};