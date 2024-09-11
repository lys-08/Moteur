/**
* \file vector3d.cpp
* This file contains the definition of all methods and attributes of the Vector3d class
*/

#include "Vector3d.h"





/**
 * @brief Default and evaluated constructor
 *
 * @param x first element
 * @param y second element
 * @param z third element
 * @param w homogeneous coordinate = fourth element which indicates if the object is a point (w=1) or a vector (w=0)
 */
Vector3d::Vector3d(float x, float y, float z, float w)
{
    x_ = x;
    y_ = y;
    z_ = z;

    w_ = w;
}

/**
 * @brief Copy constructor
 *
 * @param other the 3D vector to copy
 */
Vector3d::Vector3d(const Vector3d& other)
{
    x_ = other.x_;
    y_ = other.y_;
    z_ = other.z_;

    w_ = other.w_;
}

/**
 * @brief Dummy destructor
 */
Vector3d::~Vector3d()
{

}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

float Vector3d::getX() const
{
    return x_;
}

float Vector3d::getY() const
{
    return y_;
}

float Vector3d::getZ() const
{
    return z_;
}

float Vector3d::getW() const
{
    return w_;
}

void Vector3d::setX(float x)
{
    x_ = x;
}

void Vector3d::setY(float y)
{
    y_ = y;
}

void Vector3d::setZ(float z)
{
    z_ = z;
}

void Vector3d::setW(float w)
{
    w_ = w;
}



// ============================================================================
// Operator overloading =======================================================
// ============================================================================

Vector3d& Vector3d::operator+=(const Vector3d& v)
{
    x_ += v.x_;
    y_ += v.y_;
    z_ += v.z_;

    return *this;
}

Vector3d& Vector3d::operator+=(float& f)
{
    x_ += f;
    y_ += f;
    z_ += f;

    return *this;
}

Vector3d& Vector3d::operator-=(const Vector3d& v)
{
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;

    return *this;
}

Vector3d& Vector3d::operator-=(float& f)
{
    x_ -= f;
    y_ -= f;
    z_ -= f;

    return *this;
}

Vector3d& Vector3d::operator*=(const Vector3d& v)
{
    x_ *= v.x_;
    y_ *= v.y_;
    z_ *= v.z_;

    return *this;
}

Vector3d& Vector3d::operator*=(float& f)
{
    x_ *= f;
    y_ *= f;
    z_ *= f;

    return *this;
}

Vector3d& Vector3d::operator/=(float& f)
{
    if (f == 0)
    {
        throw std::invalid_argument("Division by zero");
    }

    x_ /= f;
    y_ /= f;
    z_ /= f;

    return *this;
}

void Vector3d::operator=(const Vector3d& v)
{
    if (this != &v)
    {
        x_ = v.x_;
        y_ = v.y_;
        z_ = v.z_;
    }
}

bool Vector3d::operator==(const Vector3d& v) const
{
    return (x_ == v.x_ && y_ == v.y_ && z_ == v.z_);
}


bool Vector3d::operator!=(const Vector3d& v) const
{
    return !(*this == v);
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief Normalise the current vector
 *
 * @return nothing
*/
void Vector3d::normalise()
{
    float length = sqrt(x_ * x_ + y_ * y_ + z_ * z_);

    if (length != 0)
    {
        x_ /= length;
        y_ /= length;
        z_ /= length;
    }
}

/**
 * @brief Performs the dot product between the current vector and the vector passed as parameter
 *
 * @param v the other vector
 * @return the dot product
*/
float Vector3d::dotProduct(const Vector3d& v) const
{
    return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}

/**
 * @brief Performs the cross product between the current vector and the vector passed as parameter
 *
 * @param v the other evctor
 * @return the cross product
*/
Vector3d Vector3d::crossProduct(const Vector3d& v) const
{
    float x = y_ * v.z_ - z_ * v.y_;
    float y = z_ * v.x_ - x_ * v.z_;
    float z = x_ * v.y_ - y_ * v.x_;

    return Vector3d(x, y, z);
}


// ============================================================================
// External operators =========================================================
// ============================================================================

/**
 * @brief Adds 2 vectors
 *
 * @param v1 first vector
 * @param v2 second vector
 * @return the addition of the vectors
*/
Vector3d operator+(const Vector3d& v1, const Vector3d& v2)
{
    Vector3d resu = Vector3d(v1);
    return resu += v2;
}

/**
 * @brief Subtracts 2 vectors
 *
 * @param v1 first vector
 * @param v2 second vector
 * @return the substraction of the vectors
*/
Vector3d operator-(const Vector3d& v1, const Vector3d& v2)
{
    Vector3d resu = Vector3d(v1);
    return resu -= v2;
}

/**
 * @brief Multiplies 2 vectors
 *
 * @param v1 first vector
 * @param v2 second vector
 * @return the multiplication of the vectors
*/
Vector3d operator*(const Vector3d& v1, const Vector3d& v2)
{
    Vector3d resu = Vector3d(v1);
    return resu *= v2;
}

/**
 * @brief Multiplies a vector and a float
 *
 * @param v the vector
 * @param f the float
 * @return the multiplication of the vector and the float
*/
Vector3d operator*(const Vector3d& v, const float f)
{
    Vector3d resu = Vector3d(v);
    return resu *= f;
}

/**
 * @brief Multiplies a float and a vector
 *
 * @param f the float
 * @param v the vector
 * @return the multiplication of the vector and the float
*/
Vector3d operator*(const float f, const Vector3d& v)
{
    return v * f;
}

/**
 * @brief Divides a vector by a float
 *
 * @param v the vector
 * @param f the float
 * @return the substraction of the vector by the float
*/
Vector3d operator/(const Vector3d& v, float& f)
{
    Vector3d resu = v;
    return resu /= f;
}