#pragma once
#include <vector>
#include <random>

namespace mlmc {

    extern std::mt19937 rng;

    // Simulates a standard Brownian motion path (W_t) using discrete steps.
    // T: Total time, num_steps: number of intervals
    std::vector<double> generate_brownian_path(double T, int num_steps);

    // Generates a Brownian path using the Paley-Wiener series representation.
    // T: Total time, num_steps: resolution of the grid, M: number of sine terms
    std::vector<double> generate_paley_wiener(double T, int num_steps, int M);

}