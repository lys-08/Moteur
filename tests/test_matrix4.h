#pragma once


class Test_matrix4
{
public:
    void tests_all();

    void tests_contructor();
    void tests_gettersAndSetters();

    void tests_operatorPlusEquals(); // TODO
    void tests_operatorTimesEquals();
    void tests_operatorTimesEquals_(); // TODO
    void tests_operatorDividedEquals(); // TODO

    void tests_det();
    void tests_t(); // TODO
    void tests_inv(); // TODO

    void tests_operatorPlus(); 
    void tests_operatorTimes();
    void tests_operatorTimes_(); // TODO
    void tests_operatorDivided(); // TODO
    void tests_vectorXmatrix4(); // TODO // TODO : choisir vecteur colonne 
    void tests_matrix4xVector(); // TODO // ou vecteur ligne
};