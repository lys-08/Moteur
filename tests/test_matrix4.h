#pragma once


class Test_matrix4
{
public:
    void tests_all();

    void tests_contructor();
    void tests_gettersAndSetters();

    void tests_operatorPlusEquals();
    void tests_operatorTimesEquals();
    void tests_operatorTimesEquals_();
    void tests_operatorDividedEquals();

    void tests_operatorPlus(); 
    void tests_operatorTimes();
    void tests_operatorTimes_();
    void tests_operatorDivided();
    void tests_matrix4xVector(); // TODO
};