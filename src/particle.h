/**
* \file particle.h
* This file contains the declaration of all methods and attributes of the Particle class
*/

#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector3d.h"


class Particle
{
private:
    Vector3d pos_;
    Vector3d dir_;
    float speed_; // strength_ ?
    float invertMass_;
    Vector3d g = Vector3d(0, 10, 0);

public:
    // Constructors
    Particle(Vector3d pos = Vector3d(), Vector3d dir = Vector3d(), float speed = 0.0);
    Particle(const Particle& other);

    // Destructor
    ~Particle();

    // Getters and Setters
    Vector3d getPos() const;
    Vector3d getDir() const;
    float getSpeed() const;
    float getInvertMass() const; //TODO
    void setDir(Vector3d dir);
    void setSpeed(float speed);
    void setInvertMass(float mass); // TODO

    // Other methods
    void move();
    void draw();
    void integrate(float temps);
};

#endif
