/**
* \file particle.h
* This file contains the declaration of all methods and attributes of the Particle class
*/

#pragma once

#include "vector3d.h"


class Particle
{
private:
    Vector3d pos_;
    Vector3d speed_;
    double mass_;
    double invertMass_;
    Vector3d accumForce_;
    double radius_;

public:
    // Constructors
    Particle(Vector3d pos = Vector3d(), Vector3d speed = Vector3d(), double mass = 1.0);
    Particle(const Particle& other);

    // Destructor
    ~Particle();

    // Getters and Setters
    Vector3d getPos() const;
    Vector3d getSpeed() const;
    double getInvertMass() const;
	Vector3d getForceAccum() const;
    double getRadius() const;
    void setSpeed(Vector3d dir);
    void setInvertMass(double mass);
	void setPos(Vector3d pos);

    // Other methods
    void draw(int type);
    void integrate(float temps);
    void addForce(const Vector3d &strength);
    void clearAccumForce();
};
