#pragma once

class Test_quaternion
{
public:
    void tests_all();

	void tests_contructors();
	void tests_gettersAndSetters();

    void tests_operatorTimesEquals();
    void tests_operatorTimesEquals_();
    void tests_operatorDividedEquals();

    void tests_identity();
    void tests_norm();
    void tests_conjugate();
    void tests_inv();
    void tests_dotProduct();
    void tests_angularMovement();
    void tests_toMatrix();

    void tests_operatorTimes();
    void tests_operatorTimes_();
    void tests_operatorTimes__();
    void tests_operatorDivided();
};