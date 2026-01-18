#ifndef CACHE_SIM_H
#define CACHE_SIM_H

#include <vector>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <algorithm> // Needed for finding the LRU victim

class CacheSim {
private:
    // This struct represents a single "Row" or "Line" in the cache.
    // We don't need 'Data', just the metadata to track hits/misses.
    struct CacheLine {
        bool valid;      // Is there data here?
        uint32_t tag;    // The unique ID of the block stored here
        uint32_t lastAccessTime; // Tracks the Least Recently Used to be kicked out when all ways are full
    };

    // Changed to establish a "set", a collection of "ways"
    // cacheSets[index][way]
    std::vector<std::vector<CacheLine>> cacheSets;

    // Configuration parameters
    uint32_t cacheSize;      // Total size in bytes
    uint32_t blockSize;      // Size of one block in bytes
    uint32_t associativity;       // Changes to N-Way (1, 2, 4, 8)

    // Bit calculations (The "systems" logic)
    uint32_t numSets;
    uint32_t numOffsetBits;
    uint32_t numIndexBits;
    uint32_t numTagBits;

    // Global sim clock (increased 1 tick per access)
    uint32_t globalTime;

    // Performance Counters
    uint64_t totalAccesses;
    uint64_t hits;
    uint64_t misses;

public:
    // Constructor: Sets up the cache size and calculates bit widths
    CacheSim(uint32_t size, uint32_t block_size, uint32_t assoc); // added 'associativity' to constructor

    bool access(uint32_t address);

    // Helper to print stats at the end
    void printStats() const;

    // Destructor
    ~CacheSim();
};

#endif