#pragma once
#include "ParticleContactGenerator.h"
class ParticleRestCollisionGenerator :
    public ParticleContactGenerator
{
    ParticleRestCollisionGenerator();

    std::vector<Particle*> particles;
    void addContact(std::vector<ParticleContact>& contacts, double time);
};

