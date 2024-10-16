/**
* \file particleContactGenerator.h
* This file contains the declaration of all methods and attributes of the ParticleContactGenerators class
*/

#pragma once

#include "particle.h"
#include "particleContact.h"

class ParticleContactGenerator
{
public:
	virtual void addContact(std::vector<ParticleContact> &contacts, double time) = 0;
};