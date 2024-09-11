/**
* \file matrix.h
* This file contains the declaration of all methods and attributes of the Matrix class
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "vector3d.h"





class Matrix
{
private:
    float mat_[4][4];


public:
    // Constructors
    Matrix(float m_00 = 0, float m_01 = 0, float m_02 = 0, float m_03 = 0, // 1ère ligne
        float m_10 = 0, float m_11 = 0, float m_12 = 0, float m_13 = 0, //2ème ligne
        float m_20 = 0, float m_21 = 0, float m_22 = 0, float m_23 = 0, // 3ème ligne
        float m_30 = 0, float m_31 = 0, float m_32 = 0, float m_33 = 0); // 4ème ligne

    // Getters and Setters
    float& operator[](std::pair<int, int> index);
    const float& operator[](std::pair<int, int> index) const;

    // Operator overloading
    Matrix operator*=(const Matrix& m);

    // Other methods
    Matrix inv();
    void initMatProj(int w, int h);
    void initMatRotX(float theta);
    void initMatRotY(float theta);
    void initMatRotZ(float theta);
};

Matrix operator*(const Matrix& m1, const Matrix& m2);
Vector3d vectorXmatrix(const Vector3d& vect, const Matrix& mat);



#endif