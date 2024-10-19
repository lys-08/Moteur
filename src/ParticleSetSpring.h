#pragma once

#include "particleForceGenerator.h"
#include "vector3d.h"

class ParticleSetSpring :
    public ParticleForceGenerator
{
    Vector3d point_;
    double k_; // elasticity coef
    double l0_; // rest length

public:
    ParticleSetSpring(Vector3d point, double k, double l0);

    void updateForce(Particle* particle, float duration);
};

