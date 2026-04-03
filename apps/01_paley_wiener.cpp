#include "brownian_motion.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

int main() {
    // The paper's Paley-Wiener example operates over the interval [0, 2*pi]
    const double PI = std::acos(-1.0);
    double T = 2.0 * PI;
    int num_steps = 500; // High resolution grid for plotting smoothly
    
    // The M values from Figure 1 in the paper
    std::vector<int> M_values = {1, 2, 5, 10, 50, 200};

    std::ofstream outfile("paley_wiener_paths.csv");
    outfile << "t";
    for (int M : M_values) {
        outfile << ",M=" << M;
    }
    outfile << "\n";

    // Generate a path for each M
    std::vector<std::vector<double>> all_paths;
    for (int M : M_values) {
        // We reset the random seed so that each M uses the exact same underlying Z_i variables
        // This is crucial to show how the terms ADD detail to the same path
        mlmc::rng.seed(123); 
        
        all_paths.push_back(mlmc::generate_paley_wiener(T, num_steps, M));
    }

    // Write to CSV
    double dt = T / num_steps;
    for (int i = 0; i <= num_steps; ++i) {
        outfile << (i * dt);
        for (size_t m_idx = 0; m_idx < M_values.size(); ++m_idx) {
            outfile << "," << all_paths[m_idx][i];
        }
        outfile << "\n";
    }

    std::cout << "Successfully generated Paley-Wiener paths. Saved to paley_wiener_paths.csv" << std::endl;
    return 0;
}