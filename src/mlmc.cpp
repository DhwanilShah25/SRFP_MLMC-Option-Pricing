#include "mlmc.hpp"
#include "brownian_motion.hpp"
#include "euler_maruyama.hpp"
#include <cmath>

namespace mlmc {
    double mlmc_pricing(
        double X0, 
        double T, 
        const std::vector<int>& N_levels, 
        const std::function<double(double, double)>& drift,
        const std::function<double(double, double)>& diffusion,
        const std::function<double(double)>& payoff,
        double discount_rate
    ) {
        int L = N_levels.size() - 1; // Max level
        double total_expectation = 0.0;

        // Level 0: Coarsest approximation (Equation 12)
        double sum_Y0 = 0.0;
        int N0 = N_levels[0];
        std::vector<double> path0(2, 0.0); 
        std::vector<double> dW0(1, 0.0);

        for (int p = 0; p < N0; ++p) {
            std::vector<double> W = generate_brownian_path(T, 1);
            dW0[0] = W[1] - W[0];
            euler_maruyama(X0, T, 1, drift, diffusion, dW0, path0);
            sum_Y0 += payoff(path0.back());
        }
        total_expectation += sum_Y0 / N0;

        // Level l > 0: The Corrections (Equation 13)
        for (int l = 1; l <= L; ++l) {
            int Nl = N_levels[l];
            int steps_fine = std::pow(2, l);
            int steps_coarse = std::pow(2, l - 1);
            
            double sum_Yl = 0.0;
            
            // Memory buffers
            std::vector<double> path_fine(steps_fine + 1, 0.0);
            std::vector<double> path_coarse(steps_coarse + 1, 0.0);
            std::vector<double> dW_fine(steps_fine, 0.0);
            std::vector<double> dW_coarse(steps_coarse, 0.0);

            for (int p = 0; p < Nl; ++p) {
                // 1. Generate the FINE Brownian path
                std::vector<double> W = generate_brownian_path(T, steps_fine);
                
                // 2. Extract fine increments and compute coarse increments by grouping pairs
                for (int i = 0; i < steps_fine; ++i) {
                    dW_fine[i] = W[i+1] - W[i];
                }
                for (int i = 0; i < steps_coarse; ++i) {
                    // This is the tight coupling: dW_coarse = dW_fine_1 + dW_fine_2
                    dW_coarse[i] = dW_fine[2*i] + dW_fine[2*i + 1];
                }

                // 3. Simulate both paths using the EXACT SAME underlying randomness
                euler_maruyama(X0, T, steps_fine, drift, diffusion, dW_fine, path_fine);
                euler_maruyama(X0, T, steps_coarse, drift, diffusion, dW_coarse, path_coarse);

                // 4. Calculate the difference in payoffs (Y_l)
                double P_fine = payoff(path_fine.back());
                double P_coarse = payoff(path_coarse.back());
                sum_Yl += (P_fine - P_coarse);
            }
            
            // Add the average correction to the total
            total_expectation += sum_Yl / Nl;
        }

        // Discount back to present value
        return std::exp(-discount_rate * T) * total_expectation;
    }
}