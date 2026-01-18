#ifndef DIRECT_MAPPED_CACHE_H
#define DIRECT_MAPPED_CACHE_H

#include <vector>
#include <cmath>
#include <cstdint>
#include <iostream>

class DirectMappedCache {
private:
    // This struct represents a single "Row" or "Line" in the cache.
    // We don't need 'Data', just the metadata to track hits/misses.
    struct CacheLine {
        bool valid;      // Is there data here?
        uint32_t tag;    // The unique ID of the block stored here
    };

    // The actual storage of the cache (a vector of cache lines)
    std::vector<CacheLine> cacheLines;

    // Configuration parameters
    uint32_t cacheSize;      // Total size in bytes
    uint32_t blockSize;      // Size of one block in bytes
    uint32_t numLines;       // How many rows total? (cacheSize / blockSize)

    // Bit calculations (The "systems" logic)
    uint32_t numOffsetBits;
    uint32_t numIndexBits;
    uint32_t numTagBits;

    // Performance Counters
    uint64_t totalAccesses;
    uint64_t hits;
    uint64_t misses;

public:
    // Constructor: Sets up the cache size and calculates bit widths
    DirectMappedCache(uint32_t size, uint32_t block_size);

    // The Core Logic: The CPU asks for an address, we return result
    // Returns true if HIT, false if MISS
    bool access(uint32_t address);

    // Helper to print stats at the end
    void printStats() const;

    // Destructor
    ~DirectMappedCache();
};

#endif