#pragma once
#include <functional>

namespace mlmc {
    // Computes the option price using Standard Monte Carlo with the Euler-Maruyama stepper
    double standard_mc(
        double X0, 
        double T, 
        int num_steps, 
        int num_paths,
        const std::function<double(double, double)>& drift,
        const std::function<double(double, double)>& diffusion,
        const std::function<double(double)>& payoff,
        double discount_rate
    );
}