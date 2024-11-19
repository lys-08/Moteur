#ifndef CONE_H
#define CONE_H

#include "rigidBody.h"
#include "vector3d.h"

class Cone : public RigidBody {
public:
    // Constructors
    Cone(float radius, float height);
    Cone(float mass, Vector3d position, Vector3d speed, Quaternion rotation, float radius, float height);

    // Getters / Setters
    float getRadius() const;
    float getHeight() const;

    void setRadius(float radius);
    void setHeight(float height);

    // Other methods
    bool isInRigidBody(const Vector3d& point) override;
    void draw() override;
    bool isColinear(const Vector3d& point);


private:
    float radius_; // Radius of the cone's base
    float height_; // Height of the cone
};

#endif // CONE_H
