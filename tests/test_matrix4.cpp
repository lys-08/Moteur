#include "test_matrix4.h"
#include "../src/matrix4.h"


// Calls all the tests methods in the Test_matrix4 class
void Test_matrix4::tests_all()
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
	tests_matrix4xVector();

	std::cout << "\033[32mAll tests of the Matrix4 class have passed !\033[0m\n" << std::endl;
}


void Test_matrix4::tests_contructor()
{
	// Default constructor
	Matrix4 default = Matrix4();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			assert(default[i][j] == 0);
		}
	}
	assert(default[3][0] == 0); assert(default[3][1] == 0); assert(default[3][2] == 0); assert(default[3][3] == 1);

	// Evaluated constructor
	Matrix4 evaluated = Matrix4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12);
	int index = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			assert(evaluated[i][j] == index);
			index++;
		}
	}
	assert(evaluated[3][0] == 0); assert(evaluated[3][1] == 0); assert(evaluated[3][2] == 0); assert(evaluated[3][3] == 1);
}

void Test_matrix4::tests_gettersAndSetters()
{
	Matrix4 m = Matrix4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12);

	// Getter
	int index = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			assert(m[i][j] == index);
			index++;
		}
	}
	assert(m[3][0] == 0); assert(m[3][1] == 0); assert(m[3][2] == 0); assert(m[3][3] == 1);

	// Setter
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[{i, j}] = m[{i, j}] * 2;
		}
	}

	index = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
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

void Test_matrix4::tests_operatorPlusEquals()
{
	Matrix4 m1 = Matrix4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12);
	Matrix4 m2(
		1, 2, 3, 4,
		1, 2, 3, 4,
		1, 2, 3, 4);

	m1 += m2;
	assert(m1[0][0] == 2);  assert(m1[0][1] == 4);  assert(m1[0][2] == 6);  assert(m1[0][3] == 8);
	assert(m1[1][0] == 6);  assert(m1[1][1] == 8);  assert(m1[1][2] == 10); assert(m1[1][3] == 12);
	assert(m1[2][0] == 10); assert(m1[2][1] == 12); assert(m1[2][2] == 14); assert(m1[2][3] == 16);
	assert(m1[3][0] == 0);  assert(m1[3][1] == 0);  assert(m1[3][2] == 0);  assert(m1[3][3] == 1);
}

void Test_matrix4::tests_operatorTimesEquals()
{
	Matrix4 m1 = Matrix4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12);
	Matrix4 m2(
		1, 2, 3, 4,
		1, 2, 3, 4,
		1, 2, 3, 4);

	m1 *= m2;
	assert(m1[0][0] == 6);  assert(m1[0][1] == 12); assert(m1[0][2] == 18); assert(m1[0][3] == 28);
	assert(m1[1][0] == 18); assert(m1[1][1] == 36); assert(m1[1][2] == 54); assert(m1[1][3] == 80);
	assert(m1[2][0] == 30); assert(m1[2][1] == 60); assert(m1[2][2] == 90); assert(m1[2][3] == 132);
	assert(m1[3][0] == 0);  assert(m1[3][1] == 0);  assert(m1[3][2] == 0);  assert(m1[3][3] == 1);
}

void Test_matrix4::tests_operatorTimesEquals_()
{
	Matrix4 m = Matrix4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12);

	m *= 2;
	assert(m[0][0] == 2);  assert(m[0][1] == 4);  assert(m[0][2] == 6);  assert(m[0][3] == 8);
	assert(m[1][0] == 10); assert(m[1][1] == 12); assert(m[1][2] == 14); assert(m[1][3] == 16);
	assert(m[2][0] == 18); assert(m[2][1] == 20); assert(m[2][2] == 22); assert(m[2][3] == 24);
	assert(m[3][0] == 0);  assert(m[3][1] == 0);  assert(m[3][2] == 0);  assert(m[3][3] == 1);
}

void Test_matrix4::tests_operatorDividedEquals()
{
	Matrix4 m = Matrix4(
		 2,  4,  6,  8,
		10, 12, 14, 16,
		18, 20, 22, 24);

	m /= 2;
	assert(m1[0][0] == 1); assert(m1[0][1] == 2);  assert(m1[0][2] == 3);  assert(m1[0][3] == 4);
	assert(m1[1][0] == 5); assert(m1[1][1] == 6);  assert(m1[1][2] == 8);  assert(m1[1][3] == 10);
	assert(m1[2][0] == 9); assert(m1[2][1] == 10); assert(m1[2][2] == 12); assert(m1[2][3] == 14);
	assert(m1[3][0] == 0); assert(m1[3][1] == 0);  assert(m1[3][2] == 0);  assert(m1[3][3] == 1);

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

void Test_matrix4::tests_det()
{
	Matrix4 m1 = Matrix4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12);
	assert(m1.det() == 0);

	Matrix4 m(
		1, 5, 3, 8,
		2, 4, 7, 2,
		4, 6, 2, 6);
	assert(m2.det() == 74);
}

void Test_matrix4::tests_t()
{
	// TODO
}

void Test_matrix4::tests_inv()
{
	// TODO
}



/* ====================================================================
 * ====================================================================
 * ====================================================================
*/

void Test_matrix4::tests_operatorPlus()
{
	Matrix4 m1 = Matrix4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12);
	Matrix4 m2(
		1, 2, 3, 4,
		1, 2, 3, 4,
		1, 2, 3, 4);

	Matrix4 m = m1 + m2;
	assert(m[0][0] == 2);  assert(m[0][1] == 4);  assert(m[0][2] == 6);  assert(m[0][3] == 8);
	assert(m[1][0] == 6);  assert(m[1][1] == 8);  assert(m[1][2] == 10); assert(m[1][3] == 12);
	assert(m[2][0] == 10); assert(m[2][1] == 12); assert(m[2][2] == 14); assert(m[2][3] == 16);
	assert(m[3][0] == 0);  assert(m[3][1] == 0);  assert(m[3][2] == 0);  assert(m[3][3] == 1);
}

void Test_matrix4::tests_operatorTimes()
{
	Matrix4 m1 = Matrix4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12);
	Matrix4 m2(
		1, 2, 3, 4,
		1, 2, 3, 4,
		1, 2, 3, 4);

	Matrix4 m3 = 31 * m2;
	assert(m3[0][0] == 6);  assert(m3[0][1] == 12); assert(m3[0][2] == 18); assert(m3[0][3] == 28);
	assert(m3[1][0] == 18); assert(m3[1][1] == 36); assert(m3[1][2] == 54); assert(m3[1][3] == 80);
	assert(m3[2][0] == 30); assert(m3[2][1] == 60); assert(m3[2][2] == 90); assert(m3[2][3] == 132);
	assert(m3[3][0] == 0);  assert(m3[3][1] == 0);  assert(m3[3][2] == 0);  assert(m3[3][3] == 1);
}

void Test_matrix4::tests_operatorTimes_()
{
	Matrix4 mx = Matrix4(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12);

	Matrix4 m = mx * 2;
	assert(m[0][0] == 2);  assert(m[0][1] == 4);  assert(m[0][2] == 6);  assert(m[0][3] == 8);
	assert(m[1][0] == 10); assert(m[1][1] == 12); assert(m[1][2] == 14); assert(m[1][3] == 16);
	assert(m[2][0] == 18); assert(m[2][1] == 20); assert(m[2][2] == 22); assert(m[2][3] == 24);
	assert(m[3][0] == 0);  assert(m[3][1] == 0);  assert(m[3][2] == 0);  assert(m[3][3] == 1);
}

void Test_matrix4::tests_operatorDivided()
{
	Matrix4 mx = Matrix4(
		2, 4, 6, 8,
		10, 12, 14, 16,
		18, 20, 22, 24);

	Matrix4 m = mx / 2;
	assert(m1[0][0] == 1); assert(m1[0][1] == 2);  assert(m1[0][2] == 3);  assert(m1[0][3] == 4);
	assert(m1[1][0] == 5); assert(m1[1][1] == 6);  assert(m1[1][2] == 8);  assert(m1[1][3] == 10);
	assert(m1[2][0] == 9); assert(m1[2][1] == 10); assert(m1[2][2] == 12); assert(m1[2][3] == 14);
	assert(m1[3][0] == 0); assert(m1[3][1] == 0);  assert(m1[3][2] == 0);  assert(m1[3][3] == 1);

	std::cout << "[operator/]" << std::endl;
	std::cout << "An error must be printed after this message (division by zero)" << std::endl;
	try {
		mx /= 0;
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "\033[31mError : " << e.what() << "\033[0m" << std::endl;
	}
}

void Test_matrix4::tests_matrix4xVector()
{
	// TODO
}