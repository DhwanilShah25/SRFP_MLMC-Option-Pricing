#pragma once
#include <vector>
#include <functional>

namespace mlmc {
    // Simulates an SDE using the Euler-Maruyama method.
    // X0: Initial value
    // T: Total time
    // num_steps: Number of discretization steps
    // drift: Function representing f(X, t)
    // diffusion: Function representing g(X, t)
    // dW: Pre-computed Brownian increments (size must be >= num_steps)
    // out_path: Pre-allocated output buffer (size must be >= num_steps + 1)
    void euler_maruyama(
        double X0, 
        double T, 
        int num_steps, 
        const std::function<double(double, double)>& drift,
        const std::function<double(double, double)>& diffusion,
        const std::vector<double>& dW, 
        std::vector<double>& out_path
    );

}