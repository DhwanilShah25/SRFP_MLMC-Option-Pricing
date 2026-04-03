#include "option_payoffs.hpp"
#include <algorithm>

namespace mlmc {
    double european_call(double X, double K) {
        return std::max(X - K, 0.0);
    }

    double digital_call(double X, double K) {
        if (X > K) return 100.0;
        if (X < K) return 0.0;
        return 50.0; 
        // The paper explicitly defines h(100) = (100+0)/2 to handle the exact strike price edge case
    }
}