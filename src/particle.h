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
    // bool invertMass_;


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
    // bool getInvertMass() const; // TODO
    void setDir(Vector3d dir);
    void setSpeed(float speed);
    // void setInvertMass(bool invertMass); // TODO

    // Other methods
    void move();
    void draw();
};

#endif