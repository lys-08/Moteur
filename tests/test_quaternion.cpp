#include "Test_quaternion.h"
#include "../src/quaternion.h"

// Calls all the tests methods in the Test_quaternion class
void Test_quaternion::tests_all()
{
	tests_contructors();
	tests_gettersAndSetters();

	tests_operatorTimesEquals();
	tests_operatorTimesEquals_();
	tests_operatorDividedEquals();

	tests_identity();
	tests_norm();
	tests_conjugate();
	tests_inv();
	tests_dotProduct();
	tests_angularMovement();
	tests_toMatrix();

	tests_operatorTimes();
	tests_operatorTimes_();
	tests_operatorTimes__();
	tests_operatorDivided();

	std::cout << "\033[32mAll tests of the Quaternion class have passed !\033[0m\n" << std::endl;
}


void Test_quaternion::tests_contructors()
{
	// Default constructor
	Quaternion default = Quaternion();
	assert(default.getW() == 0);
	assert(default.getI() == 0);
	assert(default.getJ() == 0);
	assert(default.getK() == 0);

	// Evaluated constructor
	Quaternion evaluated = Quaternion(1,2,3,4);
	assert(evaluated.getW() == 1);
	assert(evaluated.getI() == 2);
	assert(evaluated.getJ() == 3);
	assert(evaluated.getK() == 4);

	// Copy constructor
	Quaternion copy = Quaternion(evaluated);
	assert(copy.getW() == 1);
	assert(copy.getI() == 2);
	assert(copy.getJ() == 3);
	assert(copy.getK() == 4);
}

void Test_quaternion::tests_gettersAndSetters()
{
	Quaternion q = Quaternion(1, 2, 3, 1);
	assert(q.getW() == 1);
	assert(q.getI() == 2);
	assert(q.getJ() == 3);
	assert(q.getK() == 1);

	q.setW(4);
	q.setI(5);
	q.setJ(6);
	q.setK(0);

	assert(q.getW() == 4);
	assert(q.getI() == 5);
	assert(q.getJ() == 6);
	assert(q.getK() == 0);
}



/* ==================================================================== 
 * ====================================================================
 * ====================================================================
*/

void Test_quaternion::tests_operatorTimesEquals()
{
	Quaternion q1(1, 2, 3, 4);
	Quaternion q2(5, 6, 7, 8);

	q1 *= q2;
	assert(q1.getW() == -60);
	assert(q1.getI() == 12);
	assert(q1.getJ() == 30);
	assert(q1.getK() == 24);
}

void Test_quaternion::tests_operatorTimesEquals_()
{
	Quaternion q(1, 2, 3, 4);

	q *= 2;
	assert(q.getW() == 2);
	assert(q.getI() == 4);
	assert(q.getJ() == 6);
	assert(q.getK() == 8);
}

void Test_quaternion::tests_operatorDividedEquals()
{
	Quaternion q(2, 4, 6, 8);

	q /= 2;
	assert(q.getW() == 1);
	assert(q.getI() == 2);
	assert(q.getJ() == 3);
	assert(q.getK() == 4);

	std::cout << "[operator/=]" << std::endl;
	std::cout << "An error must be printed after this message (division by zero)" << std::endl;
	try {
		q /= 0;
	}
	catch (const std::invalid_argument& e) 
	{
		std::cerr << "\033[31mError : " << e.what() << "\033[0m" << std::endl;
	}
}

void Test_quaternion::tests_identity()
{
	Quaternion identity = Quaternion().identity();
	assert(identity.getW() == 1);
	assert(identity.getI() == 0);
	assert(identity.getJ() == 0);
	assert(identity.getK() == 0);
}

void Test_quaternion::tests_norm()
{
	float epsilon = 0.000001f;
	Quaternion q(1, 2, 3, 4);

	assert(std::fabs(q.norm() - 5.4772255) < epsilon);
}

void Test_quaternion::tests_conjugate()
{
	Quaternion q(1, 2, 3, 4);
	Quaternion conjugate = q.conjugate();
	assert(conjugate.getW() == 1);
	assert(conjugate.getI() == -2);
	assert(conjugate.getJ() == -3);
	assert(conjugate.getK() == -4);
}

void Test_quaternion::tests_inv()
{
	Quaternion q(1, 2, 3, 4);
	Quaternion inv = q.inv();

	float epsilon = 0.000001f;
	assert(std::fabs(inv.getW() - 0.182574) < epsilon);
	assert(std::fabs(inv.getI() + 0.365148) < epsilon);
	assert(std::fabs(inv.getJ() + 0.547722) < epsilon);
	assert(std::fabs(inv.getK() + 0.730296) < epsilon);
}

void Test_quaternion::tests_dotProduct()
{
	Quaternion q1(1, 2, 3, 4);
	Quaternion q2(5, 6, 7, 8);

	assert(q1.dotProduct(q2) == 70);
}

void Test_quaternion::tests_angularMovement()
{
	Quaternion q1 = Quaternion(1, 2, 3, 4);
	Quaternion q2 = Quaternion(5, 6, 7, 8);

	Quaternion q = q1.angularMovement(q2);

	assert(q.getW() == 70);
	assert(q.getI() == -8);
	assert(q.getJ() == 0);
	assert(q.getK() == -16);
}

void Test_quaternion::tests_toMatrix()
{
	Quaternion q(1, 2, 3, 4);
	Matrix3 quaternionMat = q.toMatrix();

	assert(quaternionMat[std::make_pair(0, 0)] == -49); assert(quaternionMat[std::make_pair(0, 1)] == 20);   assert(quaternionMat[std::make_pair(0, 2)] == 10);
	assert(quaternionMat[std::make_pair(1, 0)] == 4);   assert(quaternionMat[std::make_pair(1, 1)] == -39); assert(quaternionMat[std::make_pair(1, 2)] == 28);
	assert(quaternionMat[std::make_pair(2, 0)] == 22);  assert(quaternionMat[std::make_pair(2, 1)] == 20);  assert(quaternionMat[std::make_pair(2, 2)] == -25);
}


/* ====================================================================
 * ====================================================================
 * ====================================================================
*/

void Test_quaternion::tests_operatorTimes()
{
	Quaternion q1(1, 2, 3, 4);
	Quaternion q2(5, 6, 7, 8);

	Quaternion q = q1 * q2;
	assert(q.getW() == -60);
	assert(q.getI() == 12);
	assert(q.getJ() == 30);
	assert(q.getK() == 24);
}

void Test_quaternion::tests_operatorTimes_()
{
	Quaternion q1(1, 2, 3, 4);

	Quaternion q2 = q1 * 2;
	assert(q2.getW() == 2);
	assert(q2.getI() == 4);
	assert(q2.getJ() == 6);
	assert(q2.getK() == 8);
}

void Test_quaternion::tests_operatorTimes__()
{
	Quaternion q1(1, 2, 3, 4);

	Quaternion q2 = 2 * q1;
	assert(q2.getW() == 2);
	assert(q2.getI() == 4);
	assert(q2.getJ() == 6);
	assert(q2.getK() == 8);
}

void Test_quaternion::tests_operatorDivided()
{
	Quaternion q1(2, 4, 6, 8);

	Quaternion q2 = q1 / 2;
	assert(q2.getW() == 1);
	assert(q2.getI() == 2);
	assert(q2.getJ() == 3);
	assert(q2.getK() == 4);

	std::cout << "[operator/]" << std::endl;
	std::cout << "An error must be printed after this message (division by zero)" << std::endl;
	try {
		q1 /= 0;
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "\033[31mError : " << e.what() << "\033[0m" << std::endl;
	}
}