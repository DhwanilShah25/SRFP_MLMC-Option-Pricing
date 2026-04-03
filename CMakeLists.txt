cmake_minimum_required(VERSION 3.14)
project(MLMC_Option_Pricing CXX)

# Use C++17 for modern standard library features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory to the compiler's search path
include_directories(include)

# Define the core library (your engine)
# Define the core library (your engine)
add_library(mlmc_core
    src/brownian_motion.cpp
    src/euler_maruyama.cpp 
    src/option_payoffs.cpp 
    src/standard_mc.cpp
    src/mlmc.cpp
)

# Compile the first application: Paley-Wiener demonstration
add_executable(01_paley_wiener apps/01_paley_wiener.cpp)
target_link_libraries(01_paley_wiener mlmc_core)

# Compile the second application: Euler-Maruyama Convergence
add_executable(02_euler_convergence apps/02_euler_convergence.cpp)
target_link_libraries(02_euler_convergence mlmc_core)

# Compile the third application: Standard MC Pricing
add_executable(03_standard_mc_pricing apps/03_standard_mc_pricing.cpp)
target_link_libraries(03_standard_mc_pricing mlmc_core)

# Compile the final application: MLMC Pricing
add_executable(04_mlmc_pricing apps/04_mlmc_pricing.cpp)
target_link_libraries(04_mlmc_pricing mlmc_core)

add_executable(05_path_coupling apps/05_path_coupling.cpp)
target_link_libraries(05_path_coupling mlmc_core)

add_executable(complexity_benchmark benchmarks/complexity_benchmark.cpp)
target_link_libraries(complexity_benchmark mlmc_core)