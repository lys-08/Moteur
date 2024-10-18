#pragma once
#include "ParticleContactGenerator.h"
class ParticleStraightCable :
    public ParticleContactGenerator
{

public:
    ParticleStraightCable(Particle* particles[2], double length);

    Particle* particles_[2];
    double length_; 

    void addContact(std::vector<ParticleContact>& contacts, double time);
    double getLength() const;
};

