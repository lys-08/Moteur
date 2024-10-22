/**
* \file particleStraightCable.h
* This file contains the declaration of all methods and attributes of the ParticleStraightCable class
*/

#pragma once

#include "ParticleContactGenerator.h"

class ParticleStraightCable :
    public ParticleContactGenerator
{
    Particle* particles_[2];
    double length_;

public:
    // Constructor
    ParticleStraightCable(Particle* particles[2], double length);

    // Getters & Setters
    double getActualLength() const;

    // Other Methods
    void addContact(std::vector<ParticleContact>& contacts, double time);
};

