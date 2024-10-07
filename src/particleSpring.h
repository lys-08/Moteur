/**
* \file particleSpring.h
* This file contains the declaration of all methods and attributes of the ParticleSpring class
*/

#pragma once

#include "particleForceGenerator.h"
#include "particle.h"

class ParticleSpring :
    public ParticleForceGenerator
{
    Particle* other_;
    double k_; // elasticity coef
    double l0_; // rest length

public:
    ParticleSpring(Particle* other, double k, double l0);

    void updateForce(Particle* particle, float duration);
};

