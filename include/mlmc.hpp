#pragma once
#include <vector>
#include <functional>

namespace mlmc {
    // Computes the option price using Multilevel Monte Carlo
    // N_levels: An array defining how many paths to run at each level l
    double mlmc_pricing(
        double X0, 
        double T, 
        const std::vector<int>& N_levels, 
        const std::function<double(double, double)>& drift,
        const std::function<double(double, double)>& diffusion,
        const std::function<double(double)>& payoff,
        double discount_rate
    );
}