/**
* \file inequalitySystem.cpp
* This file contains the definition of all methods and attributes of the InequalitySystem class
*/

#include "inequalitySystem.h"
#include <algorithm>



/**
 * @brief Evaluated constructor
*/
InequalitySystem::InequalitySystem(size_t num_vars, size_t num_ineqs)
{
    vars_ = num_vars;
    ineqs_.reserve(num_ineqs);
}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

size_t InequalitySystem::num_vars() const
{
    return vars_;
}

size_t InequalitySystem::num_ineqs() const
{
    return ineqs_.size();
}



// ============================================================================
// Other methods ==============================================================
// ============================================================================

/**
 * @brief Add an equality to thelist
 *
 * @param coeffs
 * @return nothing
*/
void InequalitySystem::add_inequality(const std::vector<double>& coeffs)
{
    if (coeffs.size() != vars_)
    {
        throw std::invalid_argument("Coefficient vector size does not match the number of variables.");
    }
    ineqs_.push_back(coeffs);
}

/**
 * @brief Reduce the iquality according to the parameter
 *
 * @param var_index
 * @return an equality system
*/
InequalitySystem InequalitySystem::reduce_on(size_t var_index) const
{
    std::vector<std::vector<double>> positives;
    std::vector<std::vector<double>> negatives;
    std::vector<std::vector<double>> neutrals;

    for (const auto& inequality : ineqs_)
    {
        if (inequality.size() <= var_index) continue;

        if (inequality[var_index] > 0)
        {
            positives.push_back(inequality);
        }
        else if (inequality[var_index] < 0)
        {
            negatives.push_back(inequality);
        }
        else
        {
            neutrals.push_back(inequality);
        }
    }

    std::vector<std::vector<double>> new_inequalities;
    for (const auto& pos : positives)
    {
        for (const auto& neg : negatives)
        {
            std::vector<double> combined(vars_);

            double pos_factor = -neg[var_index];
            double neg_factor = pos[var_index];

            for (size_t i = 0; i < vars_; ++i)
            {
                combined[i] = pos_factor * pos[i] + neg_factor * neg[i];
            }

            new_inequalities.push_back(std::move(combined));
        }
    }

    // Neutral inequalities
    for (const auto& neutral : neutrals)
    {
        new_inequalities.push_back(neutral);
    }

    // Reduced inequality system
    InequalitySystem reduced_system(vars_ - 1, new_inequalities.size());

    // New equalities add to the reduced system
    for (auto& inequality : new_inequalities)
    {
        if (inequality.size() > var_index)
        {
            inequality.erase(inequality.begin() + var_index); 
        }
        reduced_system.add_inequality(std::move(inequality));
    }

    return reduced_system;
}

/**
 * @brief Print the inequality system
 *
 * @return nothing
*/
void InequalitySystem::print() const
{
    std::cout << "Numéro de variables : " << num_vars() << std::endl;
    std::cout << "Numéro d'inégalités : " << num_ineqs() << std::endl;

    // Afficher toutes les inégalités
    for (const auto& ineq : ineqs_)
    {
        for (const auto& coeff : ineq)
        {
            std::cout << coeff << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Check if the inequality system is valid
 *
 * @return true if the system is valid
*/
bool InequalitySystem::is_valid() const
{
    for (const auto& inequality : ineqs_)
    {
        if (std::all_of(inequality.begin(), inequality.end() - 1, [](double coeff) { return coeff == 0.0; }) &&
            inequality.back() < 0.0)
        {
            return false; 
        }
    }
    return true; 
}

/**
 * @brief Evaluate the system in a point
 *
 * @param var_index
 * @param values the poins to evaluate
 * @return the result of the system
*/
double InequalitySystem::calc_variable(size_t var_index, const std::vector<double>& values) const
{
    for (const auto& inequality : ineqs_)
    {
        if (inequality[var_index] != 0)
        {
            double result = inequality.back();
            for (size_t i = 0; i < values.size(); ++i)
            {
                result -= inequality[i] * values[i];
            }
            return result / inequality[var_index];
        }
    }
    throw std::logic_error("No inequality found to calculate variable.");
}

/**
 * @brief Return the number of invalid equations
 *
 * @return the number of invalid equations
*/
size_t InequalitySystem::find_invalid() const
{
    for (size_t i = 0; i < ineqs_.size(); ++i)
    {
        const auto& inequality = ineqs_[i];
        if (std::all_of(inequality.begin(), inequality.end() - 1, [](double coeff) { return coeff == 0.0; }) &&
            inequality.back() < 0.0)
        {
            return i;
        }
    }
    throw std::logic_error("No invalid inequality found.");
}
