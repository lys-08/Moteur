#pragma once


class Test_vector3d
{
public:
    void tests_all();

	void tests_contructors();
	void tests_gettersAndSetters();

	void tests_operatorPlusEquals();
    void tests_operatorMinusEquals();
    void tests_operatorTimesEquals();
    void tests_operatorDividedEquals();
    void tests_operatorAffectation();
    void tests_operatorEquals();
    void tests_operatorDifferent();

    void tests_norm();
    void tests_norm2();
    void tests_normalise(); // normalise2 uses normalise and return the result so their is no need to test it in addition to the test on normalise
    void tests_dotProduct();
    void tests_crossProduct();
    void tests_v3();

    void tests_operatorPlus();
    void tests_operatorMinus();
    void tests_operatorTimes();
    void tests_operatorTimes_();
    void tests_operatorDivided();
};

