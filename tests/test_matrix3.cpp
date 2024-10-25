#include "test_matrix3.h"
#include "../src/matrix3.h"


// Calls all the tests methods in the Test_matrix3 class
void Test_matrix3::tests_all()
{
	tests_contructor();
	tests_gettersAndSetters();

	tests_operatorTimesEquals();
	tests_operatorTimesEquals_();
	tests_operatorDividedEquals();

	tests_det();
	tests_t();
	tests_inv();

	tests_operatorTimes();
	tests_operatorTimes_();
	tests_operatorDivided();
	tests_vectorXmatrix3();
	tests_matrix3xVector();

	std::cout << "\033[32mAll tests of the Matrix3 class have passed !\033[0m\n" << std::endl;
}


void Test_matrix3::tests_contructor()
{
	// Default constructor
	Matrix3 default = Matrix3();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			assert(default[i][j] == 0);
		}
	}

	// Evaluated constructor
	Matrix3 evaluated = Matrix3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	int index = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			assert(evaluated[i][j] == index);
			index++;
		}
	}
}

void Test_matrix3::tests_gettersAndSetters()
{
	Matrix3 m = Matrix3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	// Getter
	int index = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			assert(m[i][j] == index);
			index++;
		}
	}

	// Setter
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[{i,j}] = m[{i, j}] * 2;
		}
	}

	index = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			assert(m[i][j] == index * 2);
			index++;
		}
	}
}



/* ==================================================================== 
 * ====================================================================
 * ====================================================================
*/

void Test_matrix3::tests_operatorPlusEquals()
{
	Matrix3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	Matrix3 m2(
		1, 5, 3,
		2, 4, 7,
		4, 6, 2);

	m1 += m2;
	assert(m1[0][0] == 2);  assert(m1[0][1] == 7);  assert(m1[0][2] == 6);
	assert(m1[1][0] == 6);  assert(m1[1][1] == 9);  assert(m1[1][2] == 13);
	assert(m1[2][0] == 12); assert(m1[2][1] == 14); assert(m1[2][2] == 11);
}

void Test_matrix3::tests_operatorTimesEquals()
{
	Matrix3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3 m2(
		1, 2, 3,
		1, 2, 3,
		1, 2, 3);

	m1 *= m2;
	assert(m1[0][0] == 6);  assert(m1[0][1] == 15); assert(m1[0][2] == 24);
	assert(m1[1][0] == 12); assert(m1[1][1] == 30); assert(m1[1][2] == 48);
	assert(m1[2][0] == 18); assert(m1[2][1] == 45); assert(m1[2][2] == 72);
}

void Test_matrix3::tests_operatorTimesEquals_()
{
	Matrix3 m(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	m *= 2;
	assert(m[0][0] == 2);  assert(m[0][1] == 4);  assert(m[0][2] == 6);
	assert(m[1][0] == 8);  assert(m[1][1] == 10); assert(m[1][2] == 12);
	assert(m[2][0] == 14); assert(m[2][1] == 16); assert(m[2][2] == 18);
}

void Test_matrix3::tests_operatorDividedEquals()
{
	Matrix3 m(
		2,  4,  6,
		8,  10, 12,
		14, 16, 18);

	m /= 2;
	assert(m[0][0] == 1); assert(m[0][1] == 2); assert(m[0][2] == 3);
	assert(m[1][0] == 4); assert(m[1][1] == 5); assert(m[1][2] == 6);
	assert(m[2][0] == 7); assert(m[2][1] == 8); assert(m[2][2] == 9);

	std::cout << "[operator/=]" << std::endl;
	std::cout << "An error must be printed after this message (division by zero)" << std::endl;
	try {
		m /= 0;
	}
	catch (const std::invalid_argument& e) 
	{
		std::cerr << "\033[31mError : " << e.what() << "\033[0m" << std::endl;
	}
}

void Test_matrix3::tests_det()
{
	Matrix3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	assert(m1.det() == 0);

	Matrix3 m2(
		1, 5, 3,
		2, 4, 7,
		4, 6, 2);
	assert(m2.det() == 74);
}

void Test_matrix3::tests_t()
{
	Matrix3 m(
		1, 5, 3,
		2, 4, 7,
		4, 6, 2);
	Matrix3 tm = m.t();

	assert(tm[0][0] == 1); assert(tm[0][1] == 2); assert(tm[0][2] == 4);
	assert(tm[1][0] == 5); assert(tm[1][1] == 4); assert(tm[1][2] == 6);
	assert(tm[2][0] == 3); assert(tm[2][1] == 7); assert(tm[2][2] == 2);
}

void Test_matrix3::tests_inv()
{
	Matrix3 m(
		1, 2, 3,
		0, 1, 4,
		5, 6, 0);

	Matrix3 inv = m.inv();

	assert(inv[0][0] == -24); assert(inv[0][1] == 18);  assert(inv[0][2] == 5);
	assert(inv[1][0] == 20);  assert(inv[1][1] == -15); assert(inv[1][2] == -4);
	assert(inv[2][0] == -5);  assert(inv[2][1] == 4);   assert(inv[2][2] == 1);
}



/* ====================================================================
 * ====================================================================
 * ====================================================================
*/

void Test_matrix3::tests_operatorPlus()
{
	Matrix3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	Matrix3 m2(
		1, 5, 3,
		2, 4, 7,
		4, 6, 2);

	Matrix3 m3 = m1 + m2;
	assert(m3[0][0] == 2);  assert(m3[0][1] == 7);  assert(m3[0][2] == 6);
	assert(m3[1][0] == 6);  assert(m3[1][1] == 9);  assert(m3[1][2] == 13);
	assert(m3[2][0] == 12); assert(m3[2][1] == 14); assert(m3[2][2] == 11);
}

void Test_matrix3::tests_operatorTimes()
{
	Matrix3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3 m2(
		1, 2, 3,
		1, 2, 3,
		1, 2, 3);

	Matrix3 m3 = m1 * m2;
	assert(m3[0][0] == 6);  assert(m3[0][1] == 15); assert(m3[0][2] == 24);
	assert(m3[1][0] == 12); assert(m3[1][1] == 30); assert(m3[1][2] == 48);
	assert(m3[2][0] == 18); assert(m3[2][1] == 45); assert(m3[2][2] == 72);
}

void Test_matrix3::tests_operatorTimes_()
{
	Matrix3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	Matrix3 m2 = m1 * 2;
	assert(m2[0][0] == 2);  assert(m2[0][1] == 4);  assert(m2[0][2] == 6);
	assert(m2[1][0] == 8);  assert(m2[1][1] == 10); assert(m2[1][2] == 12);
	assert(m2[2][0] == 14); assert(m2[2][1] == 16); assert(m2[2][2] == 18);
}

void Test_matrix3::tests_operatorDivided()
{
	Matrix3 m1(
		2, 4, 6,
		8, 10, 12,
		14, 16, 18);

	Matrix3 m2 = m1 / 2;
	assert(m2[0][0] == 1); assert(m2[0][1] == 2); assert(m2[0][2] == 3);
	assert(m2[1][0] == 4); assert(m2[1][1] == 5); assert(m2[1][2] == 6);
	assert(mm22][0] == 7); assert(m2[2][1] == 8); assert(m2[2][2] == 9);

	std::cout << "[operator/=]" << std::endl;
	std::cout << "An error must be printed after this message (division by zero)" << std::endl;
	try {
		m2 = m1 / 0;
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "\033[31mError : " << e.what() << "\033[0m" << std::endl;
	}
}

void Test_matrix3::tests_vectorXmatrix3()
{
	Matrix3 m(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Vector3d v(2, 4, 6);

	Vector3d mXv = VectorXmatrix3(v, m);
	assert(mXv.getX() == 14);
	assert(mXv.getY() == 22);
	assert(mXv.getZ() == 40);
}

void Test_matrix3::tests_matrix3xVector()
{
	Matrix3 m(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Vector3d v(2, 4, 6);

	Vector3d vXm = Matrix3xVector(v, m);
	assert(vXm.getX() == 60);
	assert(vXm.getY() == 72);
	assert(vXm.getZ() == 84);
}