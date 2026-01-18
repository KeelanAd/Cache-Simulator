#include <iostream>
#include "DirectMappedCache.h"

int main() {
    // ---------------------------------------------------------
    // 1. CONFIGURATION
    // ---------------------------------------------------------
    // Let's build a small cache to make the math easy to follow.
    // Cache Size: 1024 bytes (1 KB)
    // Block Size: 64 bytes
    //
    // Rows = 1024 / 64 = 16 Lines
    // ---------------------------------------------------------
    uint32_t cache_size = 1024;
    uint32_t block_size = 64;

    std::cout << "Initializing Cache..." << std::endl;
    DirectMappedCache myCache(cache_size, block_size);

    // ---------------------------------------------------------
    // 2. THE SIMULATION
    //    Access a few memory addresses.
    // ---------------------------------------------------------
    
    // Address A: 0x100 (Decimal 256)
    // In our 1KB cache, this maps to Index 4.
    std::cout << "\n--- Accessing Address 0x100 (First Time) ---" << std::endl;
    bool result = myCache.access(0x100);
    std::cout << "Result: " << (result ? "HIT" : "MISS") << std::endl; 
    // EXPECTATION: MISS (Cold start, cache is empty)

    std::cout << "\n--- Accessing Address 0x100 (Second Time) ---" << std::endl;
    result = myCache.access(0x100);
    std::cout << "Result: " << (result ? "HIT" : "MISS") << std::endl;
    // EXPECTATION: HIT (We just loaded it!)

    std::cout << "\n--- Accessing Address 0x200 (Collision!) ---" << std::endl;
    // Address 0x200 (Decimal 512). 
    // 512 is exactly 256 bytes away from 256? No.
    // 512 / 64 = Block 8. 256 / 64 = Block 4.
    // Wait, let's check the Index logic:
    // This will likely map to a different index or the same index depending on the bits.
    // Let's see what happens!
    result = myCache.access(0x200);
    std::cout << "Result: " << (result ? "HIT" : "MISS") << std::endl;

    std::cout << "\n--- Accessing Address 0x100 (Again) ---" << std::endl;
    result = myCache.access(0x100);
    std::cout << "Result: " << (result ? "HIT" : "MISS") << std::endl;


    // ---------------------------------------------------------
    // 3. FINAL REPORT
    // ---------------------------------------------------------
    std::cout << std::endl;
    myCache.printStats();

    return 0;
}