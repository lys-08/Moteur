/**
* \file particleStaticFriction.h
* This file contains the declaration of all methods and attributes of the ParticleStaticFriction class
*/

#pragma once

#include "particle.h"
#include "particleForceGenerator.h"
#include "Plane.h"

class particleStaticFriction :
    public ParticleForceGenerator
{
private:
    float mu_s;  // Static friction coefficient
    Plane surfacePlane;

public:
    // Default constructor with a standard friction coefficient
    particleStaticFriction();

    // Constructor with a custom friction coefficient
    particleStaticFriction(float coefficient, const Plane& plane);

    // Method to apply static friction force
    virtual void updateForce(Particle* particle, float duration) override;
};

