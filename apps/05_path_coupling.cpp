#include "brownian_motion.hpp"
#include "euler_maruyama.hpp"
#include <fstream>
#include <iostream>

int main() {
    double X0 = 1.0, T = 1.0, mu = 1.0, sigma = 0.5;
    auto drift = [mu](double X, double t) { return mu * X; };
    auto diffusion = [sigma](double X, double t) { return sigma * X; };

    int N_fine = 128;
    int N_coarse = 64;

    std::vector<double> path_fine(N_fine + 1, 0.0);
    std::vector<double> path_coarse(N_coarse + 1, 0.0);
    std::vector<double> dW_fine(N_fine, 0.0);
    std::vector<double> dW_coarse(N_coarse, 0.0);

    // Generate exactly ONE Brownian path
    std::vector<double> W = mlmc::generate_brownian_path(T, N_fine);
    
    for (int i = 0; i < N_fine; ++i) { dW_fine[i] = W[i+1] - W[i]; }
    for (int i = 0; i < N_coarse; ++i) { dW_coarse[i] = dW_fine[2*i] + dW_fine[2*i + 1]; }

    mlmc::euler_maruyama(X0, T, N_fine, drift, diffusion, dW_fine, path_fine);
    mlmc::euler_maruyama(X0, T, N_coarse, drift, diffusion, dW_coarse, path_coarse);

    std::ofstream outfile("path_coupling.csv");
    outfile << "t_fine,x_fine,t_coarse,x_coarse\n";
    for (int i = 0; i <= N_fine; ++i) {
        outfile << (i * (T/N_fine)) << "," << path_fine[i] << ",";
        if (i % 2 == 0) outfile << (i * (T/N_fine)) << "," << path_coarse[i/2];
        else outfile << ",";
        outfile << "\n";
    }
    std::cout << "Data saved to path_coupling.csv\n";
    return 0;
}