#pragma once


class Test_matrix3
{
public:
    void tests_all();

	void tests_contructor();
	void tests_gettersAndSetters();

    void tests_operatorTimesEquals();
    void tests_operatorTimesEquals_();
    void tests_operatorDividedEquals();

    void tests_det();
    void tests_t();
    void tests_inv();

    void tests_operatorTimes();
    void tests_operatorTimes_();
    void tests_operatorDivided();
    void tests_vectorXmatrix3();
    void tests_matrix3xVector();
};