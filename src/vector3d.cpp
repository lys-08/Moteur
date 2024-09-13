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
 * @brief Return the norm of the current vector
 *
 * @return norm of the vector
*/
float Vector3d::norm()
{
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

/**
 * @brief Return the squared norm of the current vector
 *
 * @return squared norm of the vector
*/
float Vector3d::norm2()
{
    return x_ * x_ + y_ * y_ + z_ * z_;
}

/**
 * @brief Normalise the current vector
 *
 * @return nothing
*/
void Vector3d::normalise()
{
    float length = norm();

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


std::ostream& operator<<(std::ostream& flux, const Vector3d& v)
{
    flux << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ", " << v.getW() << ")" << std::endl;;
    return flux;
}

Vector3d operator+(const Vector3d& v1, const Vector3d& v2)
{
    Vector3d resu = Vector3d(v1);
    return resu += v2;
}

Vector3d operator-(const Vector3d& v1, const Vector3d& v2)
{
    Vector3d resu = Vector3d(v1);
    return resu -= v2;
}

Vector3d operator*(const Vector3d& v1, const Vector3d& v2)
{
    Vector3d resu = Vector3d(v1);
    return resu *= v2;
}

Vector3d operator*(const Vector3d& v, const float f)
{
    Vector3d resu = Vector3d(v);
    return resu *= f;
}

Vector3d operator*(const float f, const Vector3d& v)
{
    return v * f;
}

Vector3d operator/(const Vector3d& v, float& f)
{
    Vector3d resu = v;
    return resu /= f;
}