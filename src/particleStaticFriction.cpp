#include "particleStaticFriction.h"

particleStaticFriction::particleStaticFriction()
{
	mu_s = 0.5f;
    surfacePlane = Plane(Vector3d(),Vector3d());
}

particleStaticFriction::particleStaticFriction(float coefficient, const Plane& plane)
{
	mu_s = coefficient;
    surfacePlane = plane;
}

void particleStaticFriction::updateForce(Particle* particle, float duration)
{
    // Check if the particle has finite mass (if invMass = 0, it's infinite mass)
    if (particle->getInvertMass() <= 0.0f) return;

    // Get the accumulated force applied to the particle
    Vector3d appliedForce = particle->getForceAccum(); 
    
    Vector3d surfaceNormal = surfacePlane.getNormal();
    surfaceNormal.normalise();

    // Calculate the normal force (reaction force to gravity)
    double mass = 1.0 / particle->getInvertMass();
    Vector3d gravityForce = Vector3d(0.0f, mass * 9.81f, 0.0f); // N = m * g 

    Vector3d normalForce = surfaceNormal * (gravityForce.dotProduct(surfaceNormal));

    // Calculate the maximum static friction force
    Vector3d maxStaticFriction = normalForce * mu_s;

    Vector3d tangentialForce = appliedForce - surfaceNormal * appliedForce.dotProduct(surfaceNormal);

    // If the applied force is less than or equal to the static friction force
    if (tangentialForce.norm() <= maxStaticFriction.norm())
    {
        // Apply an opposite force to cancel out the movement (neutralize the force)
        tangentialForce *= -1;
        particle->addForce(appliedForce);
    } 

}
