#include "particleStaticFriction.h"

particleStaticFriction::particleStaticFriction()
{
	mu_s = 0.5f;
}

particleStaticFriction::particleStaticFriction(float coefficient)
{
	mu_s = coefficient;
}

void particleStaticFriction::updateForce(Particle* particle, float duration)
{
    // Check if the particle has finite mass (if invMass = 0, it's infinite mass)
    if (particle->getInvertMass() <= 0.0f) return;

    // Get the accumulated force applied to the particle
    Vector3d appliedForce = particle->getForceAccum(); 

    // Calculate the normal force (reaction force to gravity)
    double mass = 1.0 / particle->getInvertMass();
    Vector3d normalForce = Vector3d(0.0f, mass * 9.81f, 0.0f); // N = m * g // ONLY IN Y ?? // ONLY PLANE SURFACES ? OR INCLINED ?

    // Calculate the maximum static friction force
    Vector3d maxStaticFriction = normalForce * mu_s;

    // If the applied force is less than or equal to the static friction force
    if (appliedForce.norm() <= maxStaticFriction.norm())
    {
        // Apply an opposite force to cancel out the movement (neutralize the force)
        appliedForce *= -1;
        particle->addForce(appliedForce);
    } 

}
