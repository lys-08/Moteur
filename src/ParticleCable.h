#pragma once
#include "ParticleContactGenerator.h"
class ParticleCable :
    public ParticleContactGenerator
{

public:
    ParticleCable(Particle* particles[2], double maxLength);

    Particle* particles_[2];
    double maxLength_;
    double elasticity_;

    void addContact(std::vector<ParticleContact>& contacts, double time);
    double getActualLength() const;
};

