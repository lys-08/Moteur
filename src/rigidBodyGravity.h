/**
* \file particleGravity.h
* This file contains the declaration of all methods and attributes of the ParticleGravity class
*/

#pragma once

#include "rigidBodyForceGenerator.h"
#include "vector3d.h"

class RigidBodyGravity :
    public RigidBodyForceGenerator
{
    Vector3d gravity_;

public:
    RigidBodyGravity(const Vector3d& g = Vector3d(0.0, -9.81, 0.0, 0.0));
    
    void updateForce(RigidBody* rigidBody, float duration);
};

