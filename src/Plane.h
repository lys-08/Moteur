#pragma once
#include "vector3d.h"
class Plane
{
private:
	Vector3d normal_;
	Vector3d point_;
public:
	Plane(Vector3d normal, Vector3d point);
	const Vector3d getNormal() const;
};

