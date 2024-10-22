/**
* \file plane.h
* This file contains the declaration of all methods and attributes of the Plane class
*/

#pragma once

#include "vector3d.h"

class Plane
{
private:
	Vector3d normal_;
	Vector3d point_;

public:
	// Constructors
	Plane(Vector3d normal = Vector3d(), Vector3d point = Vector3d(0,0,0,1));

	// Getters & Setters
	const Vector3d getNormal() const;
	const Vector3d getPoint() const;
};

