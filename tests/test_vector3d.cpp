#include "test_vector3d.h"
#include "../src/vector3d.h"

// Calls all the tests methods in the Test_vector3d class
void Test_vector3d::tests_all()
{
	tests_contructors();
	tests_gettersAndSetters();

	tests_operatorPlusEquals();
	tests_operatorMinusEquals();
	tests_operatorTimesEquals();
	tests_operatorDividedEquals();
	tests_operatorAffectation();
	tests_operatorEquals();
	tests_operatorDifferent();

	tests_norm();
	tests_norm2();
	tests_normalise();
	tests_dotProduct();
	tests_crossProduct();
	tests_v3();

	tests_operatorPlus();
	tests_operatorMinus();
	tests_operatorTimes();
	tests_operatorTimes_();
	tests_operatorDivided();

	std::cout << "\033[32mAll tests of the Vector3d class have passed !\033[0m\n" << std::endl;
}


void Test_vector3d::tests_contructors()
{
	// Default constructor
	Vector3d default = Vector3d();
	assert(default.getX() == 0);
	assert(default.getY() == 0);
	assert(default.getZ() == 0);
	assert(default.getW() == 0);

	// Evaluated constructor
	Vector3d evaluated = Vector3d(1, 2, 3, 1);
	assert(evaluated.getX() == 1);
	assert(evaluated.getY() == 2);
	assert(evaluated.getZ() == 3);
	assert(evaluated.getW() == 1);

	// Copy constructor
	Vector3d copy = Vector3d(evaluated);
	assert(copy.getX() == 1);
	assert(copy.getY() == 2);
	assert(copy.getZ() == 3);
	assert(copy.getW() == 1);
}

void Test_vector3d::tests_gettersAndSetters()
{
	Vector3d v = Vector3d(1, 2, 3, 1);
	assert(v.getX() == 1);
	assert(v.getY() == 2);
	assert(v.getZ() == 3);
	assert(v.getW() == 1);

	v.setX(4);
	v.setY(5);
	v.setZ(6);
	v.setW(0);

	assert(v.getX() == 4);
	assert(v.getY() == 5);
	assert(v.getZ() == 6);
	assert(v.getW() == 0);
}



/* ==================================================================== 
 * ====================================================================
 * ====================================================================
*/

void Test_vector3d::tests_operatorPlusEquals()
{
	Vector3d v1(1, 2, 3);
	Vector3d v2(4, 5, 6);

	v1 += v2;
	assert(v1.getX() == 5);
	assert(v1.getY() == 7);
	assert(v1.getZ() == 9);
}

void Test_vector3d::tests_operatorMinusEquals()
{
	Vector3d v1(1, 2, 3);
	Vector3d v2(4, 5, 6);

	v1 -= v2;
	assert(v1.getX() == -3);
	assert(v1.getY() == -3);
	assert(v1.getZ() == -3);
}

void Test_vector3d::tests_operatorTimesEquals()
{
	Vector3d v(1, 2, 3);

	v *= 2;
	assert(v.getX() == 2);
	assert(v.getY() == 4);
	assert(v.getZ() == 6);
}

void Test_vector3d::tests_operatorDividedEquals()
{
	Vector3d v(2, 4, 6);

	v /= 2;
	assert(v.getX() == 1);
	assert(v.getY() == 2);
	assert(v.getZ() == 3);

	std::cout << "[operator/=]" << std::endl;
	std::cout << "An error must be printed after this message (division by zero)" << std::endl;
	try {
		v /= 0;
	}
	catch (const std::invalid_argument& e) 
	{
		std::cerr << "\033[31mError : " << e.what() << "\033[0m" << std::endl;
	}
}

void Test_vector3d::tests_operatorAffectation()
{
	Vector3d v1 = Vector3d(2, 4, 6);
	Vector3d v2 = Vector3d();

	v2 = v1;
	assert(v2.getX() == 2);
	assert(v2.getY() == 4);
	assert(v2.getZ() == 6);
	assert(v2.getW() == 0);
}

void Test_vector3d::tests_operatorEquals()
{
	Vector3d v1 = Vector3d(2, 4, 6);
	Vector3d v2 = v1;
	assert(v1 == v2);

	v2.setW(1);
	assert(!(v1 == v2));

	Vector3d v3 = Vector3d(2, 4, 6);
	assert(v3 == v1);

	Vector3d v4 = Vector3d(2, 44, 6);
	assert(!(v4 == v1));
}

void Test_vector3d::tests_operatorDifferent()
{
	Vector3d v1 = Vector3d(2, 4, 6);
	Vector3d v2 = v1;
	assert(!(v1 != v2));

	v2.setW(1);
	assert(v1 != v2);

	Vector3d v3 = Vector3d(2, 4, 6);
	assert(!(v3 != v1));

	Vector3d v4 = Vector3d(2, 44, 6);
	assert(v4 != v1);
}

void Test_vector3d::tests_norm()
{
	float epsilon = 0.000001f;
	Vector3d v(1, 2, 3);

	assert(std::fabs(v.norm() - 3.7416574) < epsilon);
}

void Test_vector3d::tests_norm2()
{
	float epsilon = 0.00001f;
	Vector3d v(1, 2, 3);

	assert(v.norm2() == 14);
}

void Test_vector3d::tests_normalise()
{
	float epsilon = 0.000001f;
	Vector3d v(1, 2, 3);

	v.normalise();
	assert(std::fabs(v.getX() - 0.26726124) < epsilon);
	assert(std::fabs(v.getY() - 0.53452248) < epsilon);
	assert(std::fabs(v.getZ() - 0.80178373) < epsilon);
}

void Test_vector3d::tests_dotProduct()
{
	Vector3d v1(1, 2, 3);
	Vector3d v2(4, 5, 6);
	assert(v1.dotProduct(v2) == 32);
}

void Test_vector3d::tests_crossProduct()
{
	Vector3d v1(1, 2, 3);
	Vector3d v2(4, 5, 6);

	Vector3d v3 = v1.crossProduct(v2);
	assert(v3.getX() == -3);
	assert(v3.getY() == 6);
	assert(v3.getZ() == -3);
}

void Test_vector3d::tests_v3()
{
	Vector3d v(1, 2, 3);
	glm::vec3 glmV = v.v3();

	assert(glmV.x == 1);
	assert(glmV.y == 2);
	assert(glmV.z == 3);
}


/* ====================================================================
 * ====================================================================
 * ====================================================================
*/

void Test_vector3d::tests_operatorPlus()
{
	Vector3d v1(1, 2, 3);
	Vector3d v2(4, 5, 6);

	Vector3d v3 = v1 + v2;
	assert(v3.getX() == 5);
	assert(v3.getY() == 7);
	assert(v3.getZ() == 9);
}

void Test_vector3d::tests_operatorMinus()
{
	Vector3d v1(1, 2, 3);
	Vector3d v2(4, 5, 6);

	Vector3d v3 = v1 - v2;
	assert(v3.getX() == -3);
	assert(v3.getY() == -3);
	assert(v3.getZ() == -3);
}

void Test_vector3d::tests_operatorTimes()
{
	Vector3d v1(1, 2, 3);

	Vector3d v2 = v1 * 2;
	assert(v2.getX() == 2);
	assert(v2.getY() == 4);
	assert(v2.getZ() == 6);
}

void Test_vector3d::tests_operatorTimes_()
{
	Vector3d v1(1, 2, 3);

	Vector3d v2 = 2 * v1;
	assert(v2.getX() == 2);
	assert(v2.getY() == 4);
	assert(v2.getZ() == 6);
}

void Test_vector3d::tests_operatorDivided()
{
	Vector3d v1(2, 4, 6);

	Vector3d v2 = v1 / 2;
	assert(v2.getX() == 1);
	assert(v2.getY() == 2);
	assert(v2.getZ() == 3);

	std::cout << "[operator/]" << std::endl;
	std::cout << "An error must be printed after this message (division by zero)" << std::endl;
	try {
		v2 = v1 / 0;
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "\033[31mError : " << e.what() << "\033[0m" << std::endl;
	}
}