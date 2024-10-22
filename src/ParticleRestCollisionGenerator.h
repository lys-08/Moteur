/**
* \file particleRestCollisionGenerator.h
* This file contains the declaration of all methods and attributes of the ParticleRestCollisionGenerator class
*/

#pragma once

#include "particleContactGenerator.h"
#include "plane.h"


class ParticleRestCollisionGenerator :
    public ParticleContactGenerator
{
    std::vector<Particle*> particles_;
    Plane ground_;

public:
    // Constructor
    ParticleRestCollisionGenerator(Plane ground);

    // Getters & Setters
    void setParticles(std::vector<Particle*> particles);

    // Other Methods
    void addContact(std::vector<ParticleContact>& contacts, double time);
};

