#include "Plane.h"

Plane::Plane(Vector3d normal, Vector3d point)
{
	normal_ = normal;
	point_ = point;
}

const Vector3d Plane::getNormal() const
{
	return normal_;
}
