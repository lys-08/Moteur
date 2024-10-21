#include "particleKineticFriction.h"

particleKineticFriction::particleKineticFriction()
{
	mu_k = 0.3f;
}

particleKineticFriction::particleKineticFriction(float coefficient)
{
	mu_k = coefficient;
}

void particleKineticFriction::updateForce(Particle* particle, float duration)
{

    // Check if the particle has finite mass (if invMass = 0, it's infinite mass)
    if (particle->getInvertMass() <= 0.0f) return;

    // Get the velocity of the particle
    Vector3d velocity = particle->getSpeed();

    // Check if the particle is moving; no need to apply kinetic friction if velocity is zero
    if (velocity.norm() == 0.0f) return;

    // Calculate the normal force (reaction to gravity)
    double mass = 1.0 / particle->getInvertMass();
	Vector3d normalForce = Vector3d(0.0f, mass * 9.81f, 0.0f); // N = m * g, normal force is equal to the weight of the particle

    // Calculate the kinetic friction force magnitude
    float frictionMagnitude = normalForce.norm() * mu_k;

    // Calculate the friction force, opposite to the direction of the velocity
    Vector3d frictionForce = velocity.normalise2() * -frictionMagnitude;

    // Apply the friction force to the particle
    particle->addForce(frictionForce);

	

}
