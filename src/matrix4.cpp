/**
* \file matrix4.cpp
* This file contains the implementation of all methods and attributes of the Matrix4 class
*/

#include "matrix4.h"
#include "matrix3.h"



/**
 * @brief Default and evaluated constructor
 *
 * @param m_00 first line, first column
 * @param m_01 first line, second column
 * @param m_02 ...
 * @param m_03
 * @param m_10
 * @param m_11
 * @param m_12
 * @param m_13
 * @param m_20
 * @param m_21
 * @param m_22
 * @param m_23
 * @param m_30
 * @param m_31
 * @param m_32
 * @param m_33
*/
Matrix4::Matrix4(float m_00, float m_01, float m_02, float m_03,
                 float m_10, float m_11, float m_12, float m_13,
                 float m_20, float m_21, float m_22, float m_23,
                 float m_30, float m_31, float m_32, float m_33)
{
    mat_[0][0] = m_00;
    mat_[0][1] = m_01;
    mat_[0][2] = m_02;
    mat_[0][3] = m_03;

    mat_[1][0] = m_10;
    mat_[1][1] = m_11;
    mat_[1][2] = m_12;
    mat_[1][3] = m_13;

    mat_[2][0] = m_20;
    mat_[2][1] = m_21;
    mat_[2][2] = m_22;
    mat_[2][3] = m_23;

    mat_[3][0] = m_30;
    mat_[3][1] = m_31;
    mat_[3][2] = m_32;
    mat_[3][3] = m_33;
}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

float& Matrix4::operator[](std::pair<int, int> index)
{
    if (index.first < 0 || index.first > 3 || index.second < 0 || index.second > 3)
    {
        throw std::out_of_range("indice(s) out of range");
    }

    return mat_[index.first][index.second];
}

const float& Matrix4::operator[](std::pair<int, int> index) const
{
    if (index.first < 0 || index.first > 3 || index.second < 0 || index.second > 3)
    {
        throw std::out_of_range("indice(s) out of range");
    }

    return mat_[index.first][index.second];
}



// ============================================================================
// Operator overloading =======================================================
// ============================================================================

Matrix4 Matrix4::operator+=(const Matrix4& m)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            mat_[i][j] += m[{i, j}];
        }
    }

    return *this;
}

Matrix4 Matrix4::operator*=(const Matrix4& m)
{
    Matrix4 resu;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resu[{i, j}] = mat_[i][0] * m[{0, j}]
                            + mat_[i][1] * m[{1, j}]
                            + mat_[i][2] * m[{2, j}]
                            + mat_[i][3] * m[{3, j}];
        }
    }

    *this = resu;
    return *this;
}

Matrix4 Matrix4::operator*=(float f)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            mat_[i][j] *= f;
        }
    }

    return *this;
}

Matrix4 Matrix4::operator/=(float f)
{
    if (f == 0)
    {
        throw std::invalid_argument("Division by zero");
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            mat_[i][j] /= f;
        }
    }

    return *this;
}


// ============================================================================
// External operators =========================================================
// ============================================================================

Matrix4 operator+(const Matrix4& m1, const Matrix4& m2)
{
    Matrix4 resu = m1;
    return resu += m2;
}

Matrix4 operator*(const Matrix4& m1, const Matrix4& m2)
{
    Matrix4 resu = m1;
    return resu *= m2;
}

Matrix4 operator*(const Matrix4& m, float f)
{
    Matrix4 resu = m;
    return resu *= f;
}

Matrix4 operator/(const Matrix4& m, float f)
{
    Matrix4 resu = m;
    return resu /= f;
}

/**
 * @brief Return the result vector of the multiplication of a matrix and a vector
 * -> this is the matrix x col vector
 * 
 * @param mat the matrix to multiply
 * @param vect the column vector to multiply
 * @return the result vector
*/
Vector3d Matrix4xVector(const Matrix4& mat, const Vector3d& vect)
{
    Vector3d resu;

    float x = vect.getX() * mat[{0, 0}] + vect.getY() * mat[{0, 1}] + vect.getZ() * mat[{0, 2}] + vect.getW() * mat[{0, 3}];
    float y = vect.getX() * mat[{1, 0}] + vect.getY() * mat[{1, 1}] + vect.getZ() * mat[{1, 2}] + vect.getW() * mat[{1, 3}];
    float z = vect.getX() * mat[{2, 0}] + vect.getY() * mat[{2, 1}] + vect.getZ() * mat[{2, 2}] + vect.getW() * mat[{2, 3}];
    float w = vect.getX() * mat[{3, 0}] + vect.getY() * mat[{3, 1}] + vect.getZ() * mat[{3, 2}] + vect.getW() * mat[{3, 3}];

    if (w != 0.0f)
    {
        x /= w;
        y /= w;
        z /= w;
        w /= w;
    }

    resu.setX(x);
    resu.setY(y);
    resu.setZ(z);
    resu.setW(w);

    return resu;
}