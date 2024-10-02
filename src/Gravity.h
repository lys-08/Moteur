/**
* \file gravity.h
* This file contains the declaration of all methods and attributes of the Gravity class
*/

#pragma once

#include "particleForceGenerator.h"
#include "vector3d.h"

class Gravity :
    public ParticleForceGenerator
{
    Vector3d gravity;

    Gravity();                                              // TODO
    Gravity(const Vector3d& g = Vector3d());                // TODO
    
    void updateForce(Particle* particle, float duration);   // TODO
};

