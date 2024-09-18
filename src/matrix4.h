/**
* \file matrix4.h
* This file contains the declaration of all methods and attributes of the Matrix4 class
*/

#ifndef MATRIX4_H
#define MATRIX4_H

#include <iostream>
#include "vector3d.h"





class Matrix4
{
private:
    float mat_[4][4];


public:
    // Constructors
    Matrix4(float m_00 = 0, float m_01 = 0, float m_02 = 0, float m_03 = 0,  // first ligne
            float m_10 = 0, float m_11 = 0, float m_12 = 0, float m_13 = 0,  // second ligne
            float m_20 = 0, float m_21 = 0, float m_22 = 0, float m_23 = 0,  // third ligne
            float m_30 = 0, float m_31 = 0, float m_32 = 0, float m_33 = 0); // fourth ligne
    Matrix4(const Matrix4& other);

    // Getters and Setters
    float& operator[](std::pair<int, int> index);
    const float& operator[](std::pair<int, int> index) const;

    // Operator overloading
    Matrix4 operator*=(const Matrix4& m);
    Matrix4& operator*=(float f);
    Matrix4& operator/=(float f);

    // Other methods
    float det();
    Matrix4 t();
    Matrix4 inv();
    void initMatProj(int w, int h);
    void initMatRotX(float theta);
    void initMatRotY(float theta);
    void initMatRotZ(float theta);
};

Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Matrix4 operator*(const Matrix4& m, float f);
Matrix4 operator/(const Matrix4& m, float f);
Vector3d VectorXmatrix4(const Vector3d& vect, const Matrix4& mat);
Vector3d Matrix4xVector(const Vector3d& vect, const Matrix4& mat);



#endif