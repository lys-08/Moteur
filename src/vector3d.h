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
    float x_;
    float y_;
    float z_;

    /**
     * @brief 4th vector element that will allow us to homogenize the above attributes during projections
    */
    float w_;

public:
    // Constructors
    Vector3d(float x = 0, float y = 0, float z = 0, float w = 0);
    Vector3d(const Vector3d& other);

    // Destructor
    ~Vector3d();

    // Getters and Setters
    float getX() const;
    float getY() const;
    float getZ() const;
    float getW() const;
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setW(float w);

    // Operator overloading
    Vector3d& operator+=(const Vector3d& v);
    Vector3d& operator-=(const Vector3d& v);
    Vector3d& operator*=(const Vector3d& v);
    Vector3d& operator*=(float& f);
    Vector3d& operator/=(float& f);
    void operator=(const Vector3d& v);
    bool operator==(const Vector3d& v) const;
    bool operator!=(const Vector3d& v) const;

    // Other methods
    float norm();
    float norm2();
    void normalise();
    float dotProduct(const Vector3d& v) const;
    Vector3d crossProduct(const Vector3d& v) const;

    /**
     * @brief Transform the current vector into a glm vector
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
Vector3d operator*(const Vector3d& v, float f);
Vector3d operator*(float f, const Vector3d& v);
Vector3d operator/(const Vector3d& v, float& f);

#endif
