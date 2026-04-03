# Optimizing SDE Simulation: Multilevel Monte Carlo (MLMC)

**Author:** Dhwanil Shah

## Overview
This repository contains a C++ implementation of the Multilevel Monte Carlo (MLMC) algorithm for option valuation, based on the foundational paper by M.B. Giles (2008). 

Standard Monte Carlo simulation for Stochastic Differential Equations (SDEs) suffers from a computational complexity of $O(\epsilon^{-3})$. This engine implements MLMC using tightly coupled coarse and fine paths via the Euler-Maruyama discretization scheme, effectively acting as a recursive control variate to achieve the optimal theoretical complexity of $O(\epsilon^{-2}(\log \epsilon)^2)$.

This project bridges the gap between theoretical quantitative finance and low-latency software engineering, utilizing optimized memory management to eliminate dynamic allocation overhead in the simulation hot loops.

## Repository Structure

The workspace is organized to separate the core mathematical engine, application executables, benchmarking, and visual analysis:

* **`apps/`**: Contains the main C++ executables (e.g., Paley-Wiener generation, Euler convergence testing, Standard MC, and MLMC pricing).
* **`benchmarks/`**: Scripts and applications designed to stress-test the algorithm and measure physical wall-clock CPU time against theoretical asymptotic complexity.
* **`build/`**: CMake generation and compilation directory.
* **`include/`**: C++ header files defining the functional interfaces for SDE solvers, path generation, and option payoffs.
* **`src/`**: The core implementation of the C++ engine. Optimized for CPU cache locality by passing pre-allocated memory buffers by reference.
* **`scripts/`**: Python scripts utilizing `pandas` and `matplotlib` to parse simulation outputs and generate log-log complexity visualizations.
* **`Plots/`**: Directory containing the final generated data visualizations (Convergence, Path Coupling, Complexity scaling).
* **`references/`**: Contains academic and theoretical background materials, including the original 2008 MLMC paper by M.B. Giles and a comprehensive academic report on stochastic calculus and risk modeling.
* **`CMakeLists.txt`**: The build system configuration file.
* **`Report_of_Implementation.pdf`**: A comprehensive technical report detailing the mathematical foundations, software architecture, and empirical findings of this project.

## Key Features
1. **Euler-Maruyama Stepper:** A highly flexible, functional SDE solver capable of accepting arbitrary drift and diffusion coefficients.
2. **Empirical Convergence Proofs:** Built-in applications to empirically prove the $O(\Delta t)$ weak and $O(\Delta t^{1/2})$ strong convergence scaling required for MLMC.
3. **Memory Optimization:** Zero dynamic memory allocation (`std::vector` instantiation) inside the Monte Carlo hot loop, drastically reducing the algorithm's base constant overhead ($C$).
4. **Complexity Benchmarking:** Automated testing demonstrating the exponential time savings of MLMC over Standard MC at high precision ($\epsilon$).

## Prerequisites
To build and run this project, you will need:
* A C++ compiler supporting C++11 or higher (e.g., GCC, Clang)
* CMake (version 3.10+)
* Python 3.x (for running visualization scripts)
* Python packages: `pandas`, `matplotlib`, `numpy`

## Build Instructions
This project uses CMake for its build system. To compile the core library and all executables, run the following commands from the project root:

```bash
mkdir -p build
cd build
cmake ..
make
```

## Academic Context & Acknowledgements
This repository was engineered as the practical implementation phase of my Summer Research Fellowship Programme (SRFP) at IIT Bombay under Prof. K.S. Mallikarjuna Rao.

**For the Code & Benchmarks:** Please see Report_of_Implementation.pdf in the root directory. It details the C++ architecture, memory optimization, and complexity scaling of this specific repository.

**For the Theoretical Background:** Please see references/Intern_Report_MATS354_SRFP.pdf. This is my comprehensive academic report covering the broader quantitative finance theory studied during the fellowship, including Risk Measures, Itô Calculus, and Volatility modeling.
