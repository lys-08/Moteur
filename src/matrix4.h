/**
* \file matrix4.h
* This file contains the declaration of all methods and attributes of the Matrix4 class
*/

#pragma once

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
            float m_30 = 0, float m_31 = 0, float m_32 = 0, float m_33 = 1); // fourth ligne

    // Getters and Setters
    float& operator[](std::pair<int, int> index);
    const float& operator[](std::pair<int, int> index) const;

    // Operator overloading
    Matrix4 operator+=(const Matrix4& m);
    Matrix4 operator*=(const Matrix4& m);
    Matrix4 operator*=(float f);
    Matrix4 operator/=(float f);

    /**
     * @brief Transform the current matrix into a glm matrix
     *
     * @return a glm matrix with the coordinates of the matrix
    */
    glm::mat4 m4() {
        return glm::mat4(
            mat_[0][0], mat_[0][1], mat_[0][2], mat_[0][3],
            mat_[1][0], mat_[1][1], mat_[1][2], mat_[1][3],
            mat_[2][0], mat_[2][1], mat_[2][2], mat_[2][3],
            mat_[3][0], mat_[3][1], mat_[3][2], mat_[3][3]);
    };
};

Matrix4 operator+(const Matrix4& m1, const Matrix4& m2);
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Matrix4 operator*(const Matrix4& m, float f);
Matrix4 operator/(const Matrix4& m, float f);
Vector3d Matrix4xVector(const Matrix4& mat, const Vector3d& vect);