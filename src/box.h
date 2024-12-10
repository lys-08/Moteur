/**
* \file box.h
* This file contains the declaration of all methods and attributes of the Box class
*/

#pragma once

#include <iostream>
#include "quaternion.h"
#include "rigidBody.h"


class Box : public RigidBody
{
private:
    Vector3d w_; // width ~ x / 2
    Vector3d h_; // height ~ y / 2
    Vector3d d_; // depth ~ z / 2


public:
    // Constructors
    Box(float height = 20, float width = 20, float depth = 20);
    Box(float mass, Vector3d position = Vector3d(0, 0, 0, 1), Vector3d speed = Vector3d(0, 0, 0, 0), 
        Quaternion rotation = Quaternion(), float height = 20, float width = 20, float depth = 20);

    // Getters and Setters
    Vector3d getW();
    Vector3d getH();
    Vector3d getD();
    void setW(Vector3d w);
    void setH(Vector3d h);
    void setD(Vector3d d);

    // Other methods
    bool isInRigidBody(const Vector3d& point);
    bool isColinear(const Vector3d& force, const Vector3d& point);
    std::vector<Vector3d> getVertex();
    float calculateBoundingRadius() override; // Bounding volume
    void draw();	
};