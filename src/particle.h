/**
* \file particle.h
* This file contains the declaration of all methods and attributes of the Particle class
*/
#pragma once

#include "vector3d.h"
#include "particleSpring.h"
#include "particleSetSpring.h"

class ParticleSpring;
class ParticleSetSpring;

class Particle
{
private:
    Vector3d pos_;
    Vector3d speed_;
    double mass_;
    double invertMass_;
    Vector3d accumForce_;
    double radius_;
    
    bool hasSpring = false;
    bool hasSetSpring = false;
    ParticleSpring* spring;
    ParticleSetSpring* setSpring;

    int particleTypeDraw;

public:
    // Constructors
    Particle(Vector3d pos = Vector3d(), Vector3d speed = Vector3d(), int typeDraw = 0, double mass = 1.0);
    Particle(const Particle& other);

    // Destructor
    ~Particle();

    // Getters and Setters
    Vector3d getPos() const;
    Vector3d getSpeed() const;
    double getMass() const;
    double getInvertMass() const;
	Vector3d getForceAccum() const;
    double getRadius() const;
    bool getHasSpring();
    bool getHasSetSpring();
    ParticleSpring getSpring();
    ParticleSetSpring getSetSpring();

    void setSpeed(Vector3d dir);
    void setInvertMass(double mass);
	void setPos(Vector3d pos);
    void setSpringForce(Particle* other, double k, double l0);
    void setSetSpringForce(Vector3d point, double k, double l0);
    void removeSpringForce();
    void removeSetSpringForce();

    // Other methods
    void draw();
    void integrate(float temps);
    void addForce(const Vector3d &strength);
    void clearAccumForce();
};