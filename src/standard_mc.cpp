#include "standard_mc.hpp"
#include "brownian_motion.hpp"
#include "euler_maruyama.hpp"
#include <vector>
#include <cmath>

namespace mlmc {
    double standard_mc(
        double X0, 
        double T, 
        int num_steps, 
        int num_paths,
        const std::function<double(double, double)>& drift,
        const std::function<double(double, double)>& diffusion,
        const std::function<double(double)>& payoff,
        double discount_rate
    ) {
        double sum_payoffs = 0.0;
        std::vector<double> path(num_steps + 1, 0.0);
        std::vector<double> dW(num_steps, 0.0);

        for (int p = 0; p < num_paths; ++p) {
            // Generate Brownian increments
            std::vector<double> W = generate_brownian_path(T, num_steps);
            for(int i = 0; i < num_steps; ++i) {
                dW[i] = W[i+1] - W[i];
            }

            // Simulate the SDE path
            euler_maruyama(X0, T, num_steps, drift, diffusion, dW, path);

            // Calculate the payoff at final time T
            sum_payoffs += payoff(path.back());
        }

        // Average the payoffs and discount back to present value
        double mean_payoff = sum_payoffs / num_paths;
        return std::exp(-discount_rate * T) * mean_payoff;
    }
}