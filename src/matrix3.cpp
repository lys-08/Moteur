/**
* \file matrix3.cpp
* This file contains the definition of all methods and attributes of the Matrix3 class
*/

#include "matrix3.h"



/**
 * @brief Default and evaluated constructor
 *
 * @param m_00 first line, first column
 * @param m_01 first line, second column
 * @param m_02 ...
 * @param m_10
 * @param m_11
 * @param m_12
 * @param m_20
 * @param m_21
 * @param m_22
 * @param m_30
 * @param m_31
 * @param m_32
*/
Matrix3::Matrix3(float m_00, float m_01, float m_02,
                 float m_10, float m_11, float m_12,
                 float m_20, float m_21, float m_22,
                 float m_30, float m_31, float m_32)
{
    mat_[0][0] = m_00;
    mat_[0][1] = m_01;
    mat_[0][2] = m_02;

    mat_[1][0] = m_10;
    mat_[1][1] = m_11;
    mat_[1][2] = m_12;

    mat_[2][0] = m_20;
    mat_[2][1] = m_21;
    mat_[2][2] = m_22;
}

/**
 * @brief Copy constructor
 *
 * @param other the matrix to copy
*/
Matrix3::Matrix3(const Matrix3& other)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mat_[i][j] = other.mat_[i][j];
        }
    }
}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

float& Matrix3::operator[](std::pair<int, int> index)
{
    if (index.first < 0 || index.first > 2 || index.second < 0 || index.second > 2)
    {
        throw std::out_of_range("indice(s) out of range");
    }

    return mat_[index.first][index.second];
}

const float& Matrix3::operator[](std::pair<int, int> index) const
{
    if (index.first < 0 || index.first > 2 || index.second < 0 || index.second > 2)
    {
        throw std::out_of_range("indice(s) out of range");
    }

    return mat_[index.first][index.second];
}



// ============================================================================
// Operator overloading =======================================================
// ============================================================================

Matrix3 Matrix3::operator*=(const Matrix3& m)
{
    Matrix3 resu;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            resu[{i, j}] = mat_[i][0] * m[{0, j}]
                            + mat_[i][1] * m[{1, j}]
                            + mat_[i][2] * m[{2, j}];
        }
    }

    return resu;
}

Matrix3& Matrix3::operator*=(float f)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mat_[i][j] *= f;
        }
    }

    return *this;
}

Matrix3& Matrix3::operator/=(float f)
{
    if (f == 0)
    {
        throw std::invalid_argument("Division by zero");
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mat_[i][j] /= f;
        }
    }

    return *this;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief determines the determinant of a matrix
 *
 * @return the determinant of the matrix
*/
float Matrix3::det()
{
    return mat_[0][0] * mat_[1][1] * mat_[2][2]
            + mat_[0][1] * mat_[1][2] * mat_[2][0]
            + mat_[0][2] * mat_[1][0] * mat_[2][1]
            - mat_[0][0] * mat_[1][2] * mat_[2][1]
            - mat_[0][1] * mat_[1][0] * mat_[2][2]
            - mat_[0][2] * mat_[1][1] * mat_[2][0];
}

/**
 * @brief determines the transposed matrix
 *
 * @return the transposed matrix
*/
Matrix3 Matrix3::t()
{
    Matrix3 resu;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            resu[{i, j}] = mat_[j][i];
        }
    }
    return resu;
}


/**
 * @brief Inverts the matrix
 *
 * @return the matrix inverse
*/
Matrix3 Matrix3::inv()
{
    float det = this->det();

    if (det == 0)
    {
        throw std::invalid_argument("Det value is 0.0");
    }

    Matrix3 resu;

    resu[{0, 0}] = mat_[1][1] * mat_[2][2] - mat_[2][1] * mat_[1][2];
    resu[{0, 1}] = - mat_[1][0] * mat_[2][2] - mat_[2][0] * mat_[1][2];
    resu[{0, 2}] = mat_[1][0] * mat_[2][1] - mat_[2][0] * mat_[1][1];

    resu[{1, 0}] = - mat_[0][1] * mat_[2][2] - mat_[2][1] * mat_[0][2];
    resu[{1, 1}] = mat_[0][0] * mat_[2][2] - mat_[2][0] * mat_[0][2];
    resu[{1, 2}] = - mat_[0][0] * mat_[2][1] - mat_[2][0] * mat_[0][1];

    resu[{2, 0}] = mat_[0][1] * mat_[1][2] - mat_[1][1] * mat_[0][2];
    resu[{2, 1}] = - mat_[0][0] * mat_[1][2] - mat_[1][0] * mat_[0][2];
    resu[{2, 2}] = mat_[0][0] * mat_[1][1] - mat_[1][0] * mat_[0][1];

    return resu.t() /= det;
}



// ============================================================================
// External operators =========================================================
// ============================================================================

Matrix3 operator*(const Matrix3& m1, const Matrix3& m2)
{
    Matrix3 resu = m1;
    return resu *= m2;
}

Matrix3 operator*(const Matrix3& m, float f)
{
    Matrix3 resu = m;
    return resu *= f;
}

Matrix3 operator/(const Matrix3& m, float f)
{
    Matrix3 resu = m;
    return resu /= f;
}

/**
 * TODO : chosse line vector x matrix OR matrix x col vector
 * -> this is the line vector x matrix
*/
Vector3d VectorXmatrix3(const Vector3d& vect, const Matrix3& mat)
{
    Vector3d resu;

    float x = vect.getX() * mat[{0, 0}] + vect.getY() * mat[{1, 0}] + vect.getZ() * mat[{2, 0}];
    float y = vect.getX() * mat[{0, 1}] + vect.getY() * mat[{1, 1}] + vect.getZ() * mat[{2, 1}];
    float z = vect.getX() * mat[{0, 2}] + vect.getY() * mat[{1, 2}] + vect.getZ() * mat[{2, 2}];

    resu.setX(x);
    resu.setY(y);
    resu.setZ(z);

    return resu;
}


/**
 * TODO : chosse line vector x matrix OR matrix x col vector
 * -> this is the matrix x col vector
*/
Vector3d Matrix3xVector(const Vector3d& vect, const Matrix3& mat)
{
    Vector3d resu;

    float x = vect.getX() * mat[{0, 0}] + vect.getY() * mat[{0, 1}] + vect.getZ() * mat[{0, 2}];
    float y = vect.getX() * mat[{1, 0}] + vect.getY() * mat[{1, 1}] + vect.getZ() * mat[{1, 2}];
    float z = vect.getX() * mat[{2, 0}] + vect.getY() * mat[{2, 1}] + vect.getZ() * mat[{2, 2}];

    float w = vect.getX() * mat[{3, 0}] + vect.getY() * mat[{3, 1}] + vect.getZ() * mat[{3, 2}];

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

    return resu;
}