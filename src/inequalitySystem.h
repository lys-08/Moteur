/**
* \file inequalitySystem.h
* This file contains the implementation of all methods and attributes of the InequalitySystem class
* 
* This resolution is based on the code of Nicholas42 : https://github.com/Nicholas42/FourierMotzkin/tree/master
*/

#pragma once

#include <vector>
#include <iostream>

class InequalitySystem
{
    std::vector<std::vector<double>> ineqs_;
    size_t vars_;

public:
    InequalitySystem(size_t vars, size_t rows);
    void add_inequality(const std::vector<double>& inequality);
    bool is_valid() const;
    size_t num_vars() const;
    size_t num_ineqs() const;

    InequalitySystem reduce_on(size_t var_index) const;
    size_t find_invalid() const;
    double calc_variable(size_t var_index, const std::vector<double>& known_vars) const;

    void print() const;
};