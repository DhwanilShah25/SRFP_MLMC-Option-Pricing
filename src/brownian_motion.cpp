#include "brownian_motion.hpp"
#include <cmath>
#include <random>

namespace mlmc {

    // Global random engine (for simplicity in this project)
    std::mt19937 rng(42); // Seeded for reproducibility
    std::normal_distribution<double> standard_normal(0.0, 1.0);

    std::vector<double> generate_brownian_path(double T, int num_steps) {
        std::vector<double> W(num_steps + 1, 0.0);
        double dt = T / num_steps;
        double sqrt_dt = std::sqrt(dt);

        for (int i = 1; i <= num_steps; ++i) {
            double dW = standard_normal(rng) * sqrt_dt;
            W[i] = W[i - 1] + dW;
        }
        return W;
    }

    std::vector<double> generate_paley_wiener(double T, int num_steps, int M) {
        std::vector<double> W(num_steps + 1, 0.0);
        
        // Generate the required standard normal random variables Z_i
        std::vector<double> Z(M + 1);
        for (int i = 0; i <= M; ++i) {
            Z[i] = standard_normal(rng);
        }

        double dt = T / num_steps;
        const double pi = std::acos(-1.0);
        const double sqrt_2pi = std::sqrt(2.0 * pi);
        const double sqrt_pi = std::sqrt(pi);

        // Compute the path over the grid
        for (int i = 0; i <= num_steps; ++i) {
            double t = i * dt;
            
            // First term: Z_0 * (t / sqrt(2*pi))
            double val = Z[0] * (t / sqrt_2pi);

            // Infinite series truncated to M terms
            double sum = 0.0;
            for (int n = 1; n <= M; ++n) {
                sum += Z[n] * (std::sin(0.5 * n * t) / n);
            }
            
            val += (2.0 / sqrt_pi) * sum;
            W[i] = val;
        }
        
        return W;
    }

} 