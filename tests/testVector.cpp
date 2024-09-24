#include "testVector.h"
#include "../apps/myApps/Moteur/src/vector3d.h"

void testVector::testVector3d()
{
	Vector3d v1(1, 2, 3);

	// Verify constructor
	assert(v1.getX() == 1);
	assert(v1.getY() == 2);
	assert(v1.getZ() == 3);

	// Verify copy constructor
	Vector3d v2(v1);
	assert(v2.getX() == 1);
	assert(v2.getY() == 2);
	assert(v2.getZ() == 3);


}

void testVector::testVector3dOperator()
{
	Vector3d v1(1, 2, 3);
	Vector3d v2(4, 5, 6);

	// Verify operator +=
	v1 += v2;
	assert(v1.getX() == 5);
	assert(v1.getY() == 7);
	assert(v1.getZ() == 9);

	//Verify operator -=
	v1 -= v2;
	assert(v1.getX() == 1);
	assert(v1.getY() == 2);
	assert(v1.getZ() == 3);

	// Verify operator *=
	v1 *= v2;
	assert(v1.getX() == 4);
	assert(v1.getY() == 10);
	assert(v1.getZ() == 18);
}

void testVector::testVector3dOtherMethods()
{

	float epsilon = 0.00001f;

	Vector3d v1(1, 2, 3);

	// Verify norm

	assert(std::fabs(v1.norm() - 3.7416574) < epsilon);

	// Verify squarred norm

	assert(v1.norm2() == 14);

	// Verify normalise
	v1.normalise();
	assert(std::fabs(v1.getX() - 0.26726124) < epsilon);
	assert(std::fabs(v1.getY() - 0.53452248) < epsilon);
	assert(std::fabs(v1.getZ() - 0.80178373) < epsilon);

	// Verify dot product
	Vector3d v3(1, 2, 3);
	Vector3d v4(4, 5, 6);
	v3.dotProduct(v4) == 32;

	// Verify cross product
	Vector3d v5(1, 2, 3);
	Vector3d v6(4, 5, 6);
	Vector3d v7 = v5.crossProduct(v6);
	assert(v7.getX() == -3);
	assert(v7.getY() == 6);
	assert(v7.getZ() == -3);

	// Verify operator ==

	Vector3d v8(1, 2, 3);
	Vector3d v9(1, 2, 3);
	assert(v8 == v9);

	// Verify operator !=

	Vector3d v10(1, 2, 3);
	Vector3d v11(4, 5, 6);
	assert(v10 != v11);

	// Verify operator =

	Vector3d v12(1, 2, 3);
	Vector3d v13(4, 5, 6);
	v12 = v13;
	assert(v12.getX() == 4);

}

void testVector::testVector3dOperatorOverloading()
{
	Vector3d v1(1, 2, 3);
	Vector3d v2(4, 5, 6);

	// Verify operator +

	Vector3d v3 = v1 + v2;
	assert(v3.getX() == 5);
	assert(v3.getY() == 7);
	assert(v3.getZ() == 9);

	// Verify operator -

	Vector3d v4 = v1 - v2;
	assert(v4.getX() == -3);
	assert(v4.getY() == -3);
	assert(v4.getZ() == -3);

	// Verify operator *

	Vector3d v5 = v1 * v2;
	assert(v5.getX() == 4);
	assert(v5.getY() == 10);
	assert(v5.getZ() == 18);

	// Verify operator /

	float a = 2;
	Vector3d v8 = v1 / a;
	assert(v8.getX() == 0.5);
	assert(v8.getY() == 1);
	assert(v8.getZ() == 1.5);
}
