#include "standard_mc.hpp"
#include "mlmc.hpp"
#include "option_payoffs.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>

int main() {
    double X0 = 100.0, T = 1.0, K = 100.0, r = 0.05, sigma = 0.25;
    auto drift = [r](double X, double t) { return r * X; };
    auto diffusion = [sigma](double X, double t) { return sigma * X; };
    auto payoff = [K](double X) { return mlmc::european_call(X, K); };

    // Accuracy targets (epsilon)
    std::vector<double> epsilons = {0.05, 0.02, 0.01, 0.005};
    
    std::ofstream outfile("complexity_data.csv");
    outfile << "epsilon,std_mc_time,mlmc_time\n";

    std::cout << "Benchmarking Time Complexity (This may take a minute)...\n" << std::endl;

    for (double eps : epsilons) {
        // --- Standard MC Parameters ---
        // To achieve accuracy eps, N scales as eps^-1 and M scales as eps^-2
        int N_std = static_cast<int>(std::ceil(1.0 / eps));
        int M_std = static_cast<int>(std::ceil(100.0 / (eps * eps))); 

        // --- MLMC Parameters ---
        // Max level L scales as log(1/eps)
        int L = static_cast<int>(std::ceil(std::log2(1.0 / eps)));
        std::vector<int> N_levels(L + 1);
        for (int l = 0; l <= L; ++l) {
            // N_l scales optimally to balance variance
            N_levels[l] = static_cast<int>(std::ceil((100.0 / (eps * eps)) * (L + 1) * std::pow(2.0, -l)));
        }

        std::cout << "Target Epsilon: " << eps << " | Std MC Paths: " << M_std << " | MLMC Max Level: " << L << std::endl;

        // 1. Time Standard MC
        auto start_std = std::chrono::high_resolution_clock::now();
        mlmc::standard_mc(X0, T, N_std, M_std, drift, diffusion, payoff, r);
        auto end_std = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_std = end_std - start_std;

        // 2. Time MLMC
        auto start_mlmc = std::chrono::high_resolution_clock::now();
        mlmc::mlmc_pricing(X0, T, N_levels, drift, diffusion, payoff, r);
        auto end_mlmc = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_mlmc = end_mlmc - start_mlmc;

        outfile << eps << "," << time_std.count() << "," << time_mlmc.count() << "\n";
        std::cout << "  -> Std MC Time: " << time_std.count() << "s" << std::endl;
        std::cout << "  -> MLMC Time:   " << time_mlmc.count() << "s\n" << std::endl;
    }

    std::cout << "Benchmark saved to complexity_data.csv" << std::endl;
    return 0;
}