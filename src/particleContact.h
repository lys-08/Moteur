/**
* \file particleContact.h
* This file contains the declaration of all methods and attributes of the ParticleContacts class
*/

#pragma once

#include "particle.h"

class ParticleContact
{
public:
	Particle particles[2];

	float elasticity;
	float interpenetration;
	Vector3d normal;

	void solve();
};