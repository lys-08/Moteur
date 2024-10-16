#pragma once
#include "ParticleContactGenerator.h"
class ParticleSphericalCollisionGenerator :
    public ParticleContactGenerator
{

public:
    ParticleSphericalCollisionGenerator();

    std::vector<Particle> particles;
    void addContact(std::vector<ParticleContact>& contacts);
};

