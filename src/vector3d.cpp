/**
* \file vector3d.cpp
* This file contains the implementation of all methods and attributes of the Vector3d class
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
Vector3d::Vector3d(double x, double y, double z, double w)
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

double Vector3d::getX() const
{
    return x_;
}

double Vector3d::getY() const
{
    return y_;
}

double Vector3d::getZ() const
{
    return z_;
}

double Vector3d::getW() const
{
    return w_;
}

void Vector3d::setX(double x)
{
    x_ = x;
}

void Vector3d::setY(double y)
{
    y_ = y;
}

void Vector3d::setZ(double z)
{
    z_ = z;
}

void Vector3d::setW(double w)
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

Vector3d& Vector3d::operator-=(const Vector3d& v)
{
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;

    return *this;
}

Vector3d& Vector3d::operator*=(double f)
{
    x_ *= f;
    y_ *= f;
    z_ *= f;

    return *this;
}

Vector3d& Vector3d::operator/=(double f)
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
        w_ = v.w_;
    }
}

bool Vector3d::operator==(const Vector3d& v) const
{
    return (x_ == v.x_ && y_ == v.y_ && z_ == v.z_ && w_ == v.w_);
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
double Vector3d::norm()
{
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

/**
 * @brief Return the squared norm of the current vector
 *
 * @return squared norm of the vector
*/
double Vector3d::norm2()
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
    double length = norm();

    if (length != 0)
    {
        x_ /= length;
        y_ /= length;
        z_ /= length;
    }
}

/**
 * @brief Normalise the current vector
 *
 * @return the normalised vector
*/
Vector3d Vector3d::normalise2()
{
    Vector3d resu = *this;
    resu.normalise();

    return resu;
}

/**
 * @brief Performs the dot product between the current vector and the vector passed as parameter
 *
 * @param v the other vector
 * @return the dot product
*/
double Vector3d::dotProduct(const Vector3d& v) const
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
    double x = y_ * v.z_ - z_ * v.y_;
    double y = z_ * v.x_ - x_ * v.z_;
    double z = x_ * v.y_ - y_ * v.x_;

    return Vector3d(x, y, z);
}

double Vector3d::distance(const Vector3d& v) const
{
    return sqrt(pow(x_ - v.getX(), 2) + pow(y_ - v.getY(), 2) + pow(z_ - v.getZ(), 2));
}

void Vector3d::mod(int q)
{
    x_ = (int)x_ % q;
    y_ = (int)y_ % q;
    z_ = (int)z_ % q;
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

Vector3d operator*(const Vector3d& v, double f)
{
    Vector3d resu = Vector3d(v);
    return resu *= f;
}

Vector3d operator*(double f, const Vector3d& v)
{
    Vector3d resu = Vector3d(v);
    return resu * f;
}

Vector3d operator/(const Vector3d& v, double f)
{
    Vector3d resu = v;
    return resu /= f;
}