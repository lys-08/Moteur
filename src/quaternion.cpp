/**
* \file quaternion.cpp
* This file contains the implementation of all methods and attributes of the Quaternion class
*/

#include "quaternion.h"





/**
 * @brief Default and evaluated constructor
 */
Quaternion::Quaternion(float w, float i, float j, float k)
{
    w_ = w;
    i_ = i;
    j_ = j;
    k_ = k;
}

/**
 * @brief Copy constructor
 */
Quaternion::Quaternion(const Quaternion& other)
{
    w_ = other.w_;
    i_ = other.i_;
    j_ = other.j_;
    k_ = other.k_;
}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

float Quaternion::getW() const
{
    return w_;
}

float Quaternion::getI() const
{
    return i_;
}

float Quaternion::getJ() const
{
    return j_;
}

float Quaternion::getK() const
{
    return k_;
}

void Quaternion::setW(float w)
{
    w_ = w;
}

void Quaternion::setI(float i)
{
    i_ = i;
}

void Quaternion::setJ(float j)
{
    j_ = j;
}

void Quaternion::setK(float k)
{
    k_ = k;
}



// ============================================================================
// Operator overloading =======================================================
// ============================================================================

Quaternion& Quaternion::operator+=(const Quaternion& other)
{
    w_ += other.w_;
    i_ += other.i_;
    j_ += other.j_;
    k_ += other.k_;

    return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
    w_ = w_ * other.w_ - i_ * other.i_ - j_ * other.j_ - k_ * other.k_;
    i_ = w_ * other.w_ + i_ * other.i_ + j_ * other.j_ - k_ * other.k_;
    j_ = w_ * other.w_ - i_ * other.i_ + j_ * other.j_ + k_ * other.k_;
    k_ = w_ * other.w_ + i_ * other.i_ - j_ * other.j_ + k_ * other.k_;

    return *this;
}

Quaternion& Quaternion::operator*=(float f)
{
    w_ *= f;
    i_ *= f;
    j_ *= f;
    k_ *= f;

    return *this;
}

Quaternion& Quaternion::operator/=(float f)
{
    if (f == 0.0)
    {
        throw std::invalid_argument("Division by zero");
    }

    w_ /= f;
    i_ /= f;
    j_ /= f;
    k_ /= f;

    return *this;
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief Return the quaternion identity
 *
 * @return the quaternion identity
*/
Quaternion Quaternion::identity()
{
    return Quaternion(1, 0, 0, 0);
}

/**
 * @brief Return the norm of the current quaternion
 *
 * @return norm of the quaternion
*/
float Quaternion::norm()
{
    return sqrt(w_ * w_ + i_ * i_ + j_ * j_ + k_ + k_);
}

/**
 * @brief Return the conjugate quaternion
 *
 * @return the conjugate identity
*/
Quaternion Quaternion::conjugate()
{
    return Quaternion(w_, - i_, - j_, - k_);
}

/**
 * @brief Return the inverse quaternion
 *
 * @return the inverse identity
*/
Quaternion Quaternion::inv()
{
    float norm = this->norm();

    if (norm == 0.0)
    {
        throw std::invalid_argument("Division by zero");
    }

    return this->conjugate() /= norm;
}

/**
 * @brief Performs the dot product between the current quaternion and the quaternion passed as parameter
 *
 * @param other the other quaternion
 * @return the dot product
*/
float Quaternion::dotProduct(const Quaternion& other) const
{
    return w_ * other.w_ + i_ * other.i_ + j_ * other.j_ + k_ * other.k_;
}

/**
 * @brief Normalise the current quaternion
 *
 * @return the normalise quaternion
*/
Quaternion& Quaternion::normalise()
{
    float length = norm();

    if (length != 0)
    {
        w_ /= length;
        i_ /= length;
        j_ /= length;
        k_ /= length;
    }

    return *this;
}

/**
 * @brief Convert the quaternion to a matrix3
 *
 * @return the result matrix
*/
Matrix3 Quaternion::toMatrix()
{
    return Matrix3(
        // first line
        1 - 2 * (j_ * j_ + k_ * k_),
        2 * (i_ * j_ + k_ * w_),
        2 * (i_ * k_ - j_ * w_),
        // second line
        2 * (i_ * j_ - k_ * w_),
        1 - 2 * (i_ * i_ + k_ * k_),
        2 * (j_ * k_ + i_ * w_),
        // third line
        2 * (i_ * k_ + j_ * w_),
        2 * (j_ * k_ - i_ * w_),
        1 - 2 * (i_ * i_ + j_ * j_)
    );
}



// ============================================================================
// External operators =========================================================
// ============================================================================

Quaternion operator+(const Quaternion& v1, const Quaternion& v2)
{
    Quaternion resu = Quaternion(v1);
    return resu += v2;
}

Quaternion operator*(const Quaternion& v1, const Quaternion& v2)
{
    Quaternion resu = Quaternion(v1);
    return resu *= v2;
}

Quaternion operator*(const Quaternion& v, float f)
{
    Quaternion resu = Quaternion(v);
    return resu *= f;
}

Quaternion operator*(float f, const Quaternion& v)
{
    Quaternion resu = Quaternion(v);
    return resu * f;
}

Quaternion operator/(const Quaternion& v, float f)
{
    Quaternion resu = Quaternion(v);
    return resu /= f;
}