/**
* \file vector3d.h
* This file contains the declaration of all methods and attributes of the Vector3d class
*/

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <ofEvents.h>


class Vector3d
{
private:
    /**
     * @brief the 3 components of the vector
    */
    double x_;
    double y_;
    double z_;

    /**
     * @brief 4th vector element that will allow us to homogenize the above attributes during projections
    */
    double w_;

public:
    // Constructors
    Vector3d(double x = 0, double y = 0, double z = 0, double w = 0);
    Vector3d(const Vector3d& other);

    // Destructor
    ~Vector3d();

    // Getters and Setters
    double getX() const;
    double getY() const;
    double getZ() const;
    double getW() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setW(double w);

    // Operator overloading
    Vector3d& operator+=(const Vector3d& v);
    Vector3d& operator-=(const Vector3d& v);
    Vector3d& operator*=(const Vector3d& v);
    Vector3d& operator/=(double f);
    void operator=(const Vector3d& v);
    bool operator==(const Vector3d& v) const;
    bool operator!=(const Vector3d& v) const;

    // Other methods
    double norm();
    double norm2();
    void normalise();
    Vector3d normalise2();
    double dotProduct(const Vector3d& v) const;
    Vector3d crossProduct(const Vector3d& v) const;

    /**
     * @brief Transform the current vector doubleo a glm vector
     *
     * @return nothing
    */
    glm::vec2 v2() { return glm::vec2(x_, y_); };
    glm::vec3 v3() { return glm::vec3(x_, y_, z_); };
};


std::ostream& operator<<(std::ostream& flux, const Vector3d& v);
Vector3d operator+(const Vector3d& v1, const Vector3d& v2);
Vector3d operator-(const Vector3d& v1, const Vector3d& v2);
Vector3d operator*(const Vector3d& v1, const Vector3d& v2);
Vector3d operator*(const Vector3d& v, double f);
Vector3d operator*(double f, const Vector3d& v);
Vector3d operator/(const Vector3d& v, double& f);

#endif
