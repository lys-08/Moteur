/**
* \file matrix3.h
* This file contains the implementation of all methods and attributes of the Matrix3 class
*/

#pragma once

#include <iostream>
#include "vector3d.h"


class Matrix3
{
private:
    float mat_[3][3];


public:
    // Constructors
    Matrix3(float m_00 = 0, float m_01 = 0, float m_02 = 0,  // first ligne
            float m_10 = 0, float m_11 = 0, float m_12 = 0,  // second ligne
            float m_20 = 0, float m_21 = 0, float m_22 = 0,  // third ligne
            float m_30 = 0, float m_31 = 0, float m_32 = 0); // fourth ligne

    // Getters and Setters
    float& operator[](std::pair<int, int> index);
    const float& operator[](std::pair<int, int> index) const;

    // Operator overloading
    Matrix3 operator+=(const Matrix3& m);
    Matrix3 operator*=(const Matrix3& m);
    Matrix3 operator*=(float f);
    Matrix3 operator/=(float f);

    // Other methods
    float det();
    Matrix3 t();
    Matrix3 inv();

    /**
     * @brief Transform the current matrix into a glm matrix 4
     *
     * @return a glm matrix 4 with the coordinates of the matrix
    */
    glm::mat4 m4() {
        return glm::mat4(
            mat_[0][0], mat_[0][1], mat_[0][2], 0,
            mat_[1][0], mat_[1][1], mat_[1][2], 0,
            mat_[2][0], mat_[2][1], mat_[2][2], 0,
            0, 0, 0, 1);
    };
};

Matrix3 operator+(const Matrix3& m1, const Matrix3& m2);
Matrix3 operator*(const Matrix3& m1, const Matrix3& m2);
Matrix3 operator*(const Matrix3& m, float f);
Matrix3 operator/(const Matrix3& m, float f);
Vector3d Matrix3xVector(const Matrix3& mat, const Vector3d& vect);