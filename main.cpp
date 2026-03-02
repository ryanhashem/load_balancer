/**
 * @file main.cpp
 * @brief Entry point for the load balancer simulation
 * @details Prompts the user for simulation configuration, creates a
 *          LoadBalancer instance, and runs the simulation.
 */

#include <iostream>
#include "LoadBalancer.h"

/**
 * @brief Runs the load balancer simulation program
 * @details Collects the number of webservers and clock cycles from standard
 *          input, then executes the simulation.
 * @return 0 on successful execution
 */
int main() {
    
    int numWebservers;

    std::cout << "How many webservers would you like? " << std::endl;
    std::cin >> numWebservers;

    int numClockCycles;

    std::cout << "How many clock cycles would you like? " << std::endl;
    std::cin >> numClockCycles;

    LoadBalancer loadBalancer(1, numWebservers);
    loadBalancer.run(numClockCycles);

    return 0;
}