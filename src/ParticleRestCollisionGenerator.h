#pragma once
#include "ParticleContactGenerator.h"
#include "Plane.h"
class ParticleRestCollisionGenerator :
    public ParticleContactGenerator
{
    ParticleRestCollisionGenerator(Plane ground);

    std::vector<Particle*> particles;
    Plane ground_;
    void addContact(std::vector<ParticleContact>& contacts, double time);
};

