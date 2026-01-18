# Configurable Trace-Driven Cache Simulator

A high-performance C++ behavioral model of a CPU cache hierarchy designed for architectural performance analysis. This tool simulates memory access patterns to evaluate the impact of **Capacity**, **Associativity**, and **Block Size** on system hit rates.

## Features
* **Parameterized Design:** Configurable Cache Size, Block Size, and N-Way Set Associativity.
* **Trace-Driven Simulation:** Reads external `.trace` files containing memory addresses to drive the simulation.
* **Hardware-Accurate Decoding:** Implements bit-level address partitioning into **Tag**, **Index**, and **Offset** using bitwise shifts and masks.
* **Replacement Policy:** Fully functional **Least Recently Used (LRU)** eviction logic using a global access-time counter.
* **Performance Analytics:** Tracks Total Accesses, Hits, Misses, and calculated Hit Rates.

## Architectural Analysis Results
The simulator was used to perform a sensitivity analysis on a custom "Heavy Stress" workload. The results highlight the trade-offs between cache size and associativity.

| Configuration | Hit Rate | Conclusion |
| :--- | :--- | :--- |
| 1024B, 1-Way | 25.0% | Baseline; limited by capacity and conflicts. |
| 1024B, 2-Way | 25.0% | Bottleneck is capacity; associativity did not resolve the misses. |
| **2048B, 1-Way** | **35.0%** | **Optimal:** Doubling capacity reduced capacity misses by 40% (relative). |

### Systems-Thinking Insight
The analysis showed that for this specific workload, the system was **Capacity-Bound**. Increasing associativity (moving from 1-Way to 2-Way) did not improve performance, suggesting that the "working set" of the program was simply larger than the 1KB cache, regardless of the mapping logic.

## Getting Started

### Prerequisites
* C++ Compiler (e.g., GCC/G++ 15.2.0 or higher)
* A terminal/command line interface

### Compilation
Compile the source files using `g++`:
```bash
g++ main.cpp CacheSim.cpp -o cache_sim
