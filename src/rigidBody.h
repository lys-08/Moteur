/**
* \file rigidBody.h
* This file contains the declaration of all methods and attributes of the RigidBody class
*/

#pragma once

#include <iostream>
#include "particle.h"
#include "quaternion.h"


class RigidBody
{
private:
    Particle massCenter_;
    Quaternion rotation_;


public:
    // Constructors
    RigidBody(Particle massCenter = Particle(), Quaternion orientation = Quaternion()); // TODO

    // Getters and Setters
    Particle getMassCenter();
    Quaternion getRotation();
    void setRotation(Quaternion rotation);

    // Other methods
};