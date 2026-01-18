#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // For pretty table formatting
#include "CacheSim.h"

// Helper function to run a full simulation and return the Hit Rate
double runExperiment(uint32_t size, uint32_t block, uint32_t assoc, std::string tracePath) {
    CacheSim sim(size, block, assoc);
    std::ifstream file(tracePath);
    std::string line;

    if (!file.is_open()) return -1.0;

    while (std::getline(file, line)) {
        try {
            uint32_t addr = std::stoul(line, nullptr, 16);
            sim.access(addr);
        } catch (...) { continue; }
    }
    
    // Calculate final hit rate
    // We'll add a getter or just use the math here if stats are public
    // For this example, let's assume we want to see the printout
    sim.printStats();
    return 0.0; 
}

int main() {
    std::string traceFile = "test.trace";

    std::cout << "Starting Architectural Sensitivity Analysis..." << std::endl;
    std::cout << "=====================================================" << std::endl;

    // Experiment 1: Small Direct Mapped (Baseline)
    std::cout << "\nTEST 1: 1024B, 1-Way (Direct Mapped)" << std::endl;
    runExperiment(1024, 64, 1, traceFile);

    // Experiment 2: Same size, but increase Associativity (2-Way)
    // Goal: See if adding 'Ways' helps with conflicts
    std::cout << "\nTEST 2: 1024B, 2-Way" << std::endl;
    runExperiment(1024, 64, 2, traceFile);

    // Experiment 3: Double the total Capacity
    // Goal: See if 'Size' is more important than 'Ways'
    std::cout << "\nTEST 3: 2048B, 1-Way" << std::endl;
    runExperiment(2048, 64, 1, traceFile);

    std::cout << "\n=====================================================" << std::endl;
    std::cout << "Analysis Complete." << std::endl;

    return 0;
}