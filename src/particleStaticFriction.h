/**
* \file particleStaticFriction.h
* This file contains the declaration of all methods and attributes of the ParticleStaticFriction class
*/

#pragma once

#include "particle.h"
#include "particleForceGenerator.h"
#include "Plane.h"

class ParticleStaticFriction :
    public ParticleForceGenerator
{
private:
    float mu_s_;  // Static friction coefficient
    Plane surfacePlane_;

public:
    ParticleStaticFriction(float coefficient = 0.5f,Plane plane = Plane(Vector3d(), Vector3d()));

    virtual void updateForce(Particle* particle, float duration) override;
};

