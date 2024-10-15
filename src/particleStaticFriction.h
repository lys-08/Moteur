/**
* \file particleStaticFriction.h
* This file contains the declaration of all methods and attributes of the ParticleStaticFriction class
*/

#pragma once

#include "particle.h"
#include "particleForceGenerator.h"

class particleStaticFriction :
    public ParticleForceGenerator
{
private:
    float mu_s;  // Static friction coefficient

public:
    // Default constructor with a standard friction coefficient
    particleStaticFriction();

    // Constructor with a custom friction coefficient
    particleStaticFriction(float coefficient);

    // Method to apply static friction force
    virtual void updateForce(Particle* particle, float duration) override;
};

