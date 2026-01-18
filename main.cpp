#include <iostream>
#include "CacheSim.h"

int main() {
    // ---------------------------------------------------------
    // 1. CONFIGURATION: 2-Way Set Associative
    //    Size: 1024B, Block: 64B, Assoc: 2
    //    Sets = 1024 / (64 * 2) = 8 Sets
    // ---------------------------------------------------------
    uint32_t cache_size = 1024;
    uint32_t block_size = 64;
    uint32_t associativity = 2; 

    std::cout << "Initializing " << associativity << "-Way Cache..." << std::endl;
    CacheSim myCache(cache_size, block_size, associativity);

    // ---------------------------------------------------------
    // 2. THE STRESS TEST (Conflict Scenario)
    //    Addresses 0x000 and 0x400 both map to Set 0.
    // ---------------------------------------------------------
    
    // Access A
    std::cout << "\n--- Accessing 0x000 (Set 0, Way 0) ---" << std::endl;
    myCache.access(0x000); // MISS

    // Access B (In Direct Mapped, this would kick out 0x000)
    std::cout << "--- Accessing 0x400 (Set 0, Way 1) ---" << std::endl;
    myCache.access(0x400); // MISS

    // Re-access A
    std::cout << "--- Re-accessing 0x000 ---" << std::endl;
    bool resultA = myCache.access(0x000);
    std::cout << "0x000 Result: " << (resultA ? "HIT" : "MISS") << std::endl;

    // Re-access B
    std::cout << "--- Re-accessing 0x400 ---" << std::endl;
    bool resultB = myCache.access(0x400);
    std::cout << "0x400 Result: " << (resultB ? "HIT" : "MISS") << std::endl;

    // ---------------------------------------------------------
    // 3. THE EVICTION TEST (Filling the Set)
    //    Accessing a 3rd address (0x800) which also maps to Set 0.
    //    Since Assoc=2, someone must be kicked out (LRU).
    // ---------------------------------------------------------
    std::cout << "\n--- Accessing 0x800 (Set 0 is full, triggering LRU) ---" << std::endl;
    myCache.access(0x800); // MISS - This kicks out 0x000 (the oldest)

    std::cout << "--- Checking if 0x000 was evicted ---" << std::endl;
    bool resultEvicted = myCache.access(0x000);
    std::cout << "0x000 Result: " << (resultEvicted ? "HIT" : "MISS (Evicted!)") << std::endl;

    // 4. FINAL REPORT
    std::cout << std::endl;
    myCache.printStats();

    return 0;
}