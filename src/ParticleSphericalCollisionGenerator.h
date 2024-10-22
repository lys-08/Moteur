/**
* \file particleSetSpring.h
* This file contains the declaration of all methods and attributes of the ParticleSetSpring class
*/

#pragma once

#include "ParticleContactGenerator.h"

class ParticleSphericalCollisionGenerator :
    public ParticleContactGenerator
{
    std::vector<Particle*> particles_; // TODO : vector or array ?

public:
    // Constructor
    ParticleSphericalCollisionGenerator(); // TODO

    // Getters & Setters
    void setParticles(std::vector<Particle*> particles);

    // Other Methods
    void addContact(std::vector<ParticleContact>& contacts, double time);
};

