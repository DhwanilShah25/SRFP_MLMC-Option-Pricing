#include "standard_mc.hpp"
#include "option_payoffs.hpp"
#include <iostream>

int main() {
    // Parameters exactly matching Section 6 of the paper
    double X0 = 100.0;
    double T = 1.0;
    double K = 100.0; // Strike price
    double r = 0.05;  // Risk-free interest rate (drift)
    double sigma = 0.25; // Volatility

    auto drift = [r](double X, double t) { return r * X; };
    auto diffusion = [sigma](double X, double t) { return sigma * X; };

    // Set pricing parameters
    int num_steps = 256;    // Number of time steps per path
    int num_paths = 100000; // Number of Monte Carlo simulations

    std::cout << "Pricing European Call Option via Standard Monte Carlo..." << std::endl;
    std::cout << "Simulating " << num_paths << " paths with " << num_steps << " steps each.\n" << std::endl;

    // Price the Call Option
    auto call_payoff = [K](double X) { return mlmc::european_call(X, K); };
    double call_price = mlmc::standard_mc(X0, T, num_steps, num_paths, drift, diffusion, call_payoff, r);
    
    // Price the Digital Option
    auto digital_payoff = [K](double X) { return mlmc::digital_call(X, K); };
    double digital_price = mlmc::standard_mc(X0, T, num_steps, num_paths, drift, diffusion, digital_payoff, r);

    std::cout << "--- Results ---" << std::endl;
    std::cout << "European Call Price: $" << call_price << std::endl;
    std::cout << "Digital Call Price:  $" << digital_price << std::endl;

    return 0;
}