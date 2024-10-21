/**
* \file particleContact.h
* This file contains the declaration of all methods and attributes of the ParticleContacts class
*/

#pragma once

#include "particle.h"

class ParticleContact
{
public:
	Particle* particles[2];

	float elasticity; // the elasticity of the contact (0 = no elasticity, 1 = perfect elasticity)
	float interpenetration; // the amount of interpenetration between the two particles 
	Vector3d normal; // the normal of the contact

	void solve();
};