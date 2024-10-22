/**
* \file particleRestCollisionGenerator.h
* This file contains the declaration of all methods and attributes of the ParticleRestCollisionGenerator class
*/

#pragma once

#include "ParticleContactGenerator.h"
#include "Plane.h"


class ParticleRestCollisionGenerator :
    public ParticleContactGenerator
{
    std::vector<Particle*> particles_;
    Plane ground_;

public:
    ParticleRestCollisionGenerator(Plane ground);

    void addContact(std::vector<ParticleContact>& contacts, double time);
};

