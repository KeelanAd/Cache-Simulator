#include "CacheSim.h"
#include <iostream>

// -------------------------------------------------------------------------
// 1. CONSTRUCTOR
// -------------------------------------------------------------------------
CacheSim::CacheSim(uint32_t size, uint32_t block_size, uint32_t assoc) {
    cacheSize = size;
    blockSize = block_size;
    associativity = assoc;
    
    // Safety check: Avoid division by zero
    if (associativity == 0) associativity = 1;

    // 1. Calculate how many Sets we have
    //    Capacity / (BlockSize * Associativity)
    //    Example: 1024 bytes / (64 bytes * 2 ways) = 8 Sets
    uint32_t totalBlocks = cacheSize / blockSize;
    numSets = totalBlocks / associativity;

    // 2. Configure the 2D Vector (The spaces available)
    cacheSets.resize(numSets); // Create the rows
    for(uint32_t i = 0; i < numSets; i++) {
        // For each row, create 'N' slots (ways)
        cacheSets[i].resize(associativity);
        
        // Initialize every slot as empty
        for(uint32_t j = 0; j < associativity; j++) {
            cacheSets[i][j].valid = false;
            cacheSets[i][j].tag = 0;
            cacheSets[i][j].lastAccessTime = 0;
        }
    }

    // 3. Calculate Bit Widths (Standard log2 math)
    numOffsetBits = (uint32_t)std::log2(blockSize);
    numIndexBits = (uint32_t)std::log2(numSets); // Note: log2 of SETS, not total lines
    numTagBits = 32 - numOffsetBits - numIndexBits;

    globalTime = 0;
    totalAccesses = 0;
    hits = 0;
    misses = 0;
}

// -------------------------------------------------------------------------
// 2. ACCESS FUNCTION
// -------------------------------------------------------------------------
bool CacheSim::access(uint32_t address) {
    totalAccesses++;
    globalTime++; // Tick the clock

    // --- DECODE ADDRESS ---
    uint32_t indexMask = (1 << numIndexBits) - 1;
    uint32_t index = (address >> numOffsetBits) & indexMask;
    uint32_t tag = address >> (numOffsetBits + numIndexBits);

    // --- SEARCH THE SET (ROW) ---
    // We must check EVERY way in this specific set to see if we have a match.
    // This loops through cacheSets[index][0], cacheSets[index][1], etc.
    for(uint32_t way = 0; way < associativity; way++) {
        if(cacheSets[index][way].valid && cacheSets[index][way].tag == tag) {
            // HIT!
            hits++;
            
            // Update the "Last Seen" timestamp so we know it was used recently
            cacheSets[index][way].lastAccessTime = globalTime;
            return true;
        }
    }

    // --- IF WE REACH HERE, IT'S A MISS ---
    misses++;

    // We need to put the new data in. Search for an empty slot...
    // Option A: Look for an empty slot (invalid)
    int victimWay = -1;
    for(uint32_t way = 0; way < associativity; way++) {
        if(!cacheSets[index][way].valid) {
            victimWay = way;
            break; // Found an empty seat, grab it!
        }
    }

    // Option B: If no empty slots, we must EVICT someone (Least Recently Used Policy)
    if(victimWay == -1) {
        // Find the slot with the SMALLEST (oldest) time
        uint32_t minTime = 0xFFFFFFFF; // Max possible integer
        
        for(uint32_t way = 0; way < associativity; way++) {
            if(cacheSets[index][way].lastAccessTime < minTime) {
                minTime = cacheSets[index][way].lastAccessTime;
                victimWay = way;
            }
        }
    }

    // --- INSTALL NEW DATA ---
    cacheSets[index][victimWay].valid = true;
    cacheSets[index][victimWay].tag = tag;
    cacheSets[index][victimWay].lastAccessTime = globalTime; // Stamp it with current time

    return false;
}

// -------------------------------------------------------------------------
// 3. STATS
// -------------------------------------------------------------------------
void CacheSim::printStats() const {
    std::cout << "=== Cache Statistics ===" << std::endl;
    std::cout << "Config:         " << cacheSize << "B, " << associativity << "-Way" << std::endl;
    std::cout << "Total Accesses: " << totalAccesses << std::endl;
    std::cout << "Hits:           " << hits << std::endl;
    std::cout << "Misses:         " << misses << std::endl;
    double hitRate = (totalAccesses > 0) ? (double)hits / totalAccesses * 100.0 : 0.0;
    std::cout << "Hit Rate:       " << hitRate << "%" << std::endl;
}

CacheSim::~CacheSim() {}