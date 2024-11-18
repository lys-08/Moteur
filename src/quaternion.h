/**
* \file quaternion.h
* This file contains the declaration of all methods and attributes of the Quaternion class
*/

#pragma once

#include <iostream>
#include "matrix3.h"


class Quaternion
{
private:
    float w_;
    float i_;
    float j_;
    float k_;


public:
    // Constructors
    Quaternion(float w = 0, float i = 0, float j = 0, float k = 0);
    Quaternion(const Quaternion& other);

    // Getters and Setters
    float getW() const;
    float getI() const;
    float getJ() const;
    float getK() const;
    void setW(float w);
    void setI(float i);
    void setJ(float j);
    void setK(float k);

    // Operator overloading
    Quaternion operator+=(const Quaternion& other);
    Quaternion operator*=(const Quaternion& other);
    Quaternion operator*=(float f);
    Quaternion operator/=(float f);

    // Other methods
    Quaternion identity();
    float norm();
    Quaternion conjugate();
    Quaternion inv();
    float dotProduct(const Quaternion& other) const;
    void normalise();
    Quaternion exponentiation(int t); // TODO : comment + fix
    Quaternion angularMovement(const Quaternion& other);

    Matrix3 toMatrix();
};

Quaternion operator+(const Quaternion& q1, const Quaternion& q2); 
Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
Quaternion operator*(const Quaternion& q, float f);
Quaternion operator*(float f, const Quaternion& q);
Quaternion operator/(const Quaternion& q, float f);