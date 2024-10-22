/**
* \file particleContact.h
* This file contains the declaration of all methods and attributes of the ParticleContact class
*/

#pragma once

#include "particle.h"

class ParticleContact
{
	Particle* particles_[2];

	float elasticity_; // elasticity of the contact (0 = no elasticity, 1 = perfect elasticity)
	float interpenetration_; // the amount of interpenetration between the two particles 
	Vector3d normal_;

public:
	ParticleContact(Particle* particles[2], float elasticity, float interpenetration, Vector3d normal);

	void solve();
};