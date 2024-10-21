/**
* \file particleGravity.h
* This file contains the declaration of all methods and attributes of the ParticleGravity class
*/

#pragma once

#include "particleForceGenerator.h"
#include "vector3d.h"

class ParticleGravity :
    public ParticleForceGenerator
{
    Vector3d gravity_;

public:
    ParticleGravity(const Vector3d& g = Vector3d(0.0, -9.81, 0.0, 0.0));
    
    void updateForce(Particle* particle, float duration);
};

