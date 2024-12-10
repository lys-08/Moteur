/**
* \file cone.h
* This file contains the declaration of all methods and attributes of the Cone class
*/

#pragma once

#include "rigidBody.h"
#include "vector3d.h"

class Cone : public RigidBody 
{
    float radius_; // Radius of the cone's base
    float height_; // Height of the cone

public:
    // Constructors
    Cone(float radius, float height);
    Cone(float mass, Vector3d position, Vector3d speed, Quaternion rotation, float radius, float height);

    // Getters & Setters
    float getRadius() const;
    float getHeight() const;
    void setRadius(float radius);
    void setHeight(float height);

    // Other methods
    bool isInRigidBody(const Vector3d& point) override;
    bool isColinear(const Vector3d& force, const Vector3d& point);
    std::vector<Vector3d> getVertex();
	float calculateBoundingRadius() override; // Bounding Volume
    void draw() override;
};
