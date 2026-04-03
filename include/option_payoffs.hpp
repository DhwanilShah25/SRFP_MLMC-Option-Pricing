#pragma once

namespace mlmc {
    // European call option payoff: max(X - K, 0)
    double european_call(double X, double K);

    // Digital call option payoff: 100 if X > K, 0 if X < K
    double digital_call(double X, double K);
}