#include "brownian_motion.hpp"
#include "euler_maruyama.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>

int main() {
    // SDE Parameters (Geometric Brownian Motion)
    double X0 = 1.0;
    double T = 1.0;
    double mu = 1.0;    // Drift
    double sigma = 0.5; // Volatility

    // Define the drift and diffusion functions for GBM
    auto drift = [mu](double X, double t) { return mu * X; };
    auto diffusion = [sigma](double X, double t) { return sigma * X; };

    // Convergence testing parameters
    int num_paths = 10000; // M: Number of paths to average over for stable statistics
    std::vector<int> step_sizes = {16, 32, 64, 128, 256, 512, 1024}; // N

    std::ofstream outfile("euler_convergence.csv");
    outfile << "dt,strong_error,weak_error\n";

    std::cout << "Running Euler-Maruyama convergence tests..." << std::endl;

    for (int N : step_sizes) {
        double dt = T / N;
        
        double sum_strong_error = 0.0;
        double sum_exact_final = 0.0;
        double sum_approx_final = 0.0;

        // Pre-allocate memory buffer for the solver to reuse, preventing allocation overhead
        std::vector<double> approx_path(N + 1, 0.0);

        for (int p = 0; p < num_paths; ++p) {
            // 1. Generate the true Brownian path
            std::vector<double> W = mlmc::generate_brownian_path(T, N);
            
            // Extract the increments (dW)
            std::vector<double> dW(N);
            for(int i = 0; i < N; ++i) {
                dW[i] = W[i+1] - W[i];
            }

            // 2. Compute the exact solution at the final time T
            // Exact GBM formula: X_T = X_0 * exp((mu - 0.5 * sigma^2)*T + sigma * W_T)
            double W_T = W.back(); 
            double exact_final = X0 * std::exp((mu - 0.5 * sigma * sigma) * T + sigma * W_T);

            // 3. Compute the Euler-Maruyama approximation
            mlmc::euler_maruyama(X0, T, N, drift, diffusion, dW, approx_path);
            double approx_final = approx_path.back();

            // 4. Accumulate errors
            // Strong error cares about the absolute difference on THIS specific path
            sum_strong_error += std::abs(exact_final - approx_final);
            
            // Weak error cares about accumulating the raw values to find the mean later
            sum_exact_final += exact_final;
            sum_approx_final += approx_final;
        }

        // Calculate final averages
        double strong_error = sum_strong_error / num_paths;
        
        // Weak error is the absolute difference of the averages
        double mean_exact = sum_exact_final / num_paths;
        double mean_approx = sum_approx_final / num_paths;
        double weak_error = std::abs(mean_exact - mean_approx);

        outfile << dt << "," << strong_error << "," << weak_error << "\n";
        std::cout << "N = " << N << " | dt = " << dt 
                  << " | Strong Err: " << strong_error 
                  << " | Weak Err: " << weak_error << std::endl;
    }

    std::cout << "Results saved to euler_convergence.csv" << std::endl;
    return 0;
}