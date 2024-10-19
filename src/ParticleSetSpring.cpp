#include "ParticleSetSpring.h"

ParticleSetSpring::ParticleSetSpring(Vector3d point, double k, double l0) : k_(k),l0_(l0)
{
	point_ = point;
}

void ParticleSetSpring::updateForce(Particle* particle, float duration)
{
    Vector3d dist = point_ - particle->getPos();
    auto norm = dist.norm();

    Vector3d force = k_ * (l0_ - norm) * dist.normalise2();
    particle->addForce(force);
}
