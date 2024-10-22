/**
* \file particleSetSpring.h
* This file contains the declaration of all methods and attributes of the ParticleSetSpring class
*/

#pragma once

#include "particleForceGenerator.h"
#include "vector3d.h"

class ParticleSetSpring : // SetSpring is the spring between a particle and a point in space (not another particle)
    public ParticleForceGenerator
{
    Vector3d point_;
    double k_; // elasticity coef
    double l0_; // rest length

public:
    ParticleSetSpring(Vector3d point, double k, double l0);

    void updateForce(Particle* particle, float duration);
};

