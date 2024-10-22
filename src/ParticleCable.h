/**
* \file particleCable.h
* This file contains the declaration of all methods and attributes of the ParticleCable class
*/

#pragma once

#include "ParticleContactGenerator.h"


class ParticleCable :
    public ParticleContactGenerator
{
    Particle* particles_[2];
    double maxLength_;
    double elasticity_;

public:
    ParticleCable(Particle* particles[2], double maxLength, double elasticity_); // TODO : elasticity ?

    void addContact(std::vector<ParticleContact>& contacts, double time);
    double getActualLength() const;
};