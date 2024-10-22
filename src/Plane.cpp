/**
* \file plane.cpp
* This file contains the implementation of all methods and attributes of the Plane class
*/

#include "Plane.h"


/**
 * @brief Default and evaluated constructor
 */
Plane::Plane(Vector3d normal, Vector3d point)
{
	normal_ = normal;
	point_ = point;
}


// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

const Vector3d Plane::getNormal() const
{
	return normal_;
}
