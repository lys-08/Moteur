#include "ineq.h"
#include <algorithm>

InequalitySystem::InequalitySystem(size_t num_vars, size_t num_ineqs)
    : vars_(num_vars), ineqs_()
{
    ineqs_.reserve(num_ineqs);
}

void InequalitySystem::add_inequality(const std::vector<double>& coeffs)
{
    if (coeffs.size() != vars_)
    {
        throw std::invalid_argument("Coefficient vector size does not match the number of variables.");
    }
    ineqs_.push_back(coeffs);
}

size_t InequalitySystem::num_vars() const
{
    return vars_;
}

size_t InequalitySystem::num_ineqs() const
{
    return ineqs_.size();
}
/*
const std::vector<std::vector<double>>& InequalitySystem::get_inequalities() const
{
    return ineqs_;
}*/

InequalitySystem InequalitySystem::reduce_on(size_t var_index) const
{
    std::vector<std::vector<double>> positives;
    std::vector<std::vector<double>> negatives;
    std::vector<std::vector<double>> neutrals;

    for (const auto& inequality : ineqs_)
    {
        if (inequality.size() <= var_index) {
            continue; // Evitez un accès hors limites
        }

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

    // Ajouter les inégalités neutres
    for (const auto& neutral : neutrals)
    {
        new_inequalities.push_back(neutral);
    }

    // Créer un nouveau système d'inégalités réduit
    InequalitySystem reduced_system(vars_ - 1, new_inequalities.size());

    // Ajouter les nouvelles inégalités au système réduit
    for (auto& inequality : new_inequalities)
    {
        if (inequality.size() > var_index)
        {
            inequality.erase(inequality.begin() + var_index); // Suppression de la variable
        }
        reduced_system.add_inequality(std::move(inequality));
    }

    // Retourner le système réduit
    return reduced_system;
}

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



bool InequalitySystem::is_valid() const
{

    // Vérification de contradictions évidentes
    for (const auto& inequality : ineqs_)
    {
        // Vérification si tous les coefficients sauf le dernier sont nuls et si le dernier coefficient est négatif (contradiction évidente)
        if (std::all_of(inequality.begin(), inequality.end() - 1, [](double coeff) { return coeff == 0.0; }) &&
            inequality.back() < 0.0)
        {
            return false; // Inégalité contradictoire
        }
    }

    return true; // Si aucune contradiction n'est trouvée, le système est valide
}


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
