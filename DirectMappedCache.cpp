#include "DirectMappedCache.h"

// -------------------------------------------------------------------------
// 1. THE CONSTRUCTOR
//    Calculates how wide our address wires need to be (Tag, Index, Offset).
// -------------------------------------------------------------------------
DirectMappedCache::DirectMappedCache(uint32_t size, uint32_t block_size) {
    cacheSize = size;
    blockSize = block_size;
    
    // Calculate total rows (lines)
    numLines = cacheSize / blockSize;

    // Allocate the simulated hardware rows
    cacheLines.resize(numLines);

    // Initialize cache to empty
    for(int i = 0; i < numLines; i++) {
        cacheLines[i].valid = false;
        cacheLines[i].tag = 0;
    }

    // CALCULATE BIT WIDTHS
    // standard log2 math to find out how many bits we need
    numOffsetBits = (uint32_t)std::log2(blockSize);
    numIndexBits = (uint32_t)std::log2(numLines);
    
    // The Tag is the remaining upper bits
    numTagBits = 32 - numOffsetBits - numIndexBits;

    // Initialize counters
    totalAccesses = 0;
    hits = 0;
    misses = 0;
}

// -------------------------------------------------------------------------
// 2. THE ACCESS FUNCTION (The Core Logic)
// -------------------------------------------------------------------------
bool DirectMappedCache::access(uint32_t address) {
    totalAccesses++;

    // --- DECODE ADDRESS ---
    // 1. Get Index: Shift out offset, then mask to keep only index bits
    uint32_t indexMask = (1 << numIndexBits) - 1;
    uint32_t index = (address >> numOffsetBits) & indexMask;

    // 2. Get Tag: Shift everything else away
    uint32_t tag = address >> (numOffsetBits + numIndexBits);

    // --- CHECK CACHE ---
    CacheLine &line = cacheLines[index];

    // --- HIT/MISS LOGIC ---
    if (line.valid && line.tag == tag) {
        hits++;
        return true; // HIT
    } else {
        misses++;
        // Update state on Miss (Simulate fetching from RAM)
        line.valid = true;
        line.tag = tag;
        return false; // MISS
    }
}

// -------------------------------------------------------------------------
// 3. STATS REPORTING
// -------------------------------------------------------------------------
void DirectMappedCache::printStats() const {
    std::cout << "=== Cache Statistics ===" << std::endl;
    std::cout << "Total Accesses: " << totalAccesses << std::endl;
    std::cout << "Hits:           " << hits << std::endl;
    std::cout << "Misses:         " << misses << std::endl;
    
    double hitRate = (totalAccesses > 0) ? (double)hits / totalAccesses * 100.0 : 0.0;
    std::cout << "Hit Rate:       " << hitRate << "%" << std::endl;
}

DirectMappedCache::~DirectMappedCache() {
    // Vector cleans itself up
}