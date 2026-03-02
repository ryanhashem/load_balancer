#include <iostream>
#include "LoadBalancer.h"

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