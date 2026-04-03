#include "mlmc.hpp"
#include "option_payoffs.hpp"
#include <iostream>
#include <vector>

int main() {
    // Parameters (Matching the Standard MC script)
    double X0 = 100.0;
    double T = 1.0;
    double K = 100.0;
    double r = 0.05;
    double sigma = 0.25;

    auto drift = [r](double X, double t) { return r * X; };
    auto diffusion = [sigma](double X, double t) { return sigma * X; };

    // Define the number of paths per level (N_l)
    // Level 0 gets 2 million paths (cheap!). Level 6 (dt = 1/64) only gets 5,000 paths.
    std::vector<int> N_levels = {2000000, 500000, 100000, 50000, 20000, 10000, 5000};
    
    std::cout << "Pricing European Call Option via Multilevel Monte Carlo..." << std::endl;
    std::cout << "Max refinement level L = " << N_levels.size() - 1 << std::endl;

    // Price the Call Option
    auto call_payoff = [K](double X) { return mlmc::european_call(X, K); };
    double call_price = mlmc::mlmc_pricing(X0, T, N_levels, drift, diffusion, call_payoff, r);
    
    // Price the Digital Option
    auto digital_payoff = [K](double X) { return mlmc::digital_call(X, K); };
    double digital_price = mlmc::mlmc_pricing(X0, T, N_levels, drift, diffusion, digital_payoff, r);

    std::cout << "\n--- Results ---" << std::endl;
    std::cout << "European Call Price: $" << call_price << std::endl;
    std::cout << "Digital Call Price:  $" << digital_price << std::endl;

    return 0;
}