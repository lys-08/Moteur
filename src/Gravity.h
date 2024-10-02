#pragma once

#include "ParticleForceGenerator.h"
#include "src/vector3d.h"

class Gravity :
    public ParticleForceGenerator
{
    Vector3d gravity;

    Gravity();
    Gravity(const Vector3d& g = Vector3d());
    
    void updateForce(Particle* particle, float duration);
};

