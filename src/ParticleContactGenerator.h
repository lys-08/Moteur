/**
* \file particleContactGenerator.h
* This file contains the declaration of all methods and attributes of the ParticleContactGenerators class
*/

#pragma once

#include "particle.h"

class ParticleContactGenerator
{
public:
	virtual void addContact() const = 0; //todo
};