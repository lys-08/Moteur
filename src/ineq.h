#ifndef INEQ_HPP
#define INEQ_HPP

#include <vector>
#include <iostream>

class InequalitySystem
{
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

private:
    std::vector<std::vector<double>> ineqs_;
    size_t vars_;
};

#endif
