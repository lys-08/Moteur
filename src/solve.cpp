#include "solve.h"
#include <algorithm>

namespace FourierMotzkin
{

    // Build inequalities for the two sets of points
    InequalitySystem build_inequality_system(const std::vector<Vector3d>& left, const std::vector<Vector3d>& right)
    {
        size_t num_vars = 4; // a, b, c, d
        size_t num_ineqs = left.size() + right.size();

        InequalitySystem system(num_vars, num_ineqs);

        // Add inequalities for the left object: f(x, y, z) <= 0
        for (const auto& point : left)
        {
            system.add_inequality({ point.getX(), point.getY(), point.getZ(), 0.0}); // ax + by + cz + d <= 0
        }

        // Add inequalities for the right object: f(x, y, z) > 0 (as -f(x, y, z) <= -1)
        for (const auto& point : right)
        {
            system.add_inequality({ -point.getX(), -point.getY(), -point.getZ(), -1.0}); // -ax - by - cz - d <= -1
        }

        return system;
    }

    std::vector<InequalitySystem> reduce_system(InequalitySystem system) {
        std::vector<InequalitySystem> steps;
        steps.push_back(system);

        // Continue reducing until we have no more inequalities
        while (system.num_ineqs() > 0 && system.num_vars() > 1) {
            InequalitySystem new_system = system.reduce_on(system.num_vars() - 1); // Réduire la dernière variable
            steps.push_back(new_system);
            system = std::move(new_system);
        }

        // Ajouter une étape finale avec 0 variables et inégalités
        if (system.num_ineqs() == 0) {
            steps.push_back(system);
        }

        return steps;
    }


    std::vector<double> recover_variables(const std::vector<InequalitySystem>& steps)
    {
        size_t num_vars = steps.front().num_vars();
        std::vector<double> solution(num_vars, 0.0);

        for (size_t var = 0; var < num_vars; ++var)
        {
            // Calcule la valeur de chaque variable en partant du dernier système réduit
            solution[var] = steps[var].calc_variable(var, solution);
        }

        return solution;
    }


    // Determine if there exists a separating plane
    bool has_separating_plane(const std::vector<Vector3d>& left, const std::vector<Vector3d>& right)
    {
        // Build the inequality system
        InequalitySystem system = build_inequality_system(left, right);

        if (!system.is_valid()) {
            return false;  // Le système est déjà invalide, retournez false
        }

        //std::cout << "Système initial : \n";
        //system.print();

        // Reduce the system using Fourier-Motzkin elimination
        std::vector<InequalitySystem> steps = reduce_system(std::move(system));

        for (size_t i = 0; i < steps.size(); ++i)
        {
            if (!steps[i].is_valid()) {
                return false;
            }
        }

        //std::cout << "before is valid" << std::endl;
        // If the system is infeasible, return false (collision exists)
        if (steps.back().is_valid())
        {
            return true;
        }
        return false;
        //std::cout << "after is valid" << std::endl;
        /*// Otherwise, recover the solution
        auto solution = recover_variables(steps);
        
        // Check if the solution is trivial (a = b = c = d = 0)
        return std::any_of(solution.begin(), solution.end(), [](double coeff) { return coeff != 0.0; });*/
    }

} // namespace FourierMotzkin
