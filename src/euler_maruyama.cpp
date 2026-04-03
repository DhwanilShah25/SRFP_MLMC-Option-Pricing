#include "euler_maruyama.hpp"
#include <stdexcept>

namespace mlmc {

    void euler_maruyama(
        double X0, 
        double T, 
        int num_steps, 
        const std::function<double(double, double)>& drift,
        const std::function<double(double, double)>& diffusion,
        const std::vector<double>& dW, 
        std::vector<double>& out_path
    ) {
        // Safety checks
        if (out_path.size() < num_steps + 1) {
            throw std::invalid_argument("out_path buffer is too small.");
        }
        if (dW.size() < num_steps) {
            throw std::invalid_argument("Brownian increments buffer is too small.");
        }

        double dt = T / num_steps;
        
        // Set initial condition
        out_path[0] = X0;

        // The hot loop: compute the path
        for (int i = 0; i < num_steps; ++i) {
            double current_X = out_path[i];
            double t = i * dt;
            
            // X_{n+1} = X_n + f(X_n, t)*dt + g(X_n, t)*dW_n
            out_path[i + 1] = current_X 
                            + drift(current_X, t) * dt 
                            + diffusion(current_X, t) * dW[i];
        }
    }

} 