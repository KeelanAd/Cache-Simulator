## Architectural Analysis Results

The simulator was used to compare cache configurations on a small synthetic
workload (`test.trace`, 20 accesses, 64-byte blocks). The trace has two phases:

1. **Ping-pong phase:** three addresses (`0x100`, `0x500`, `0x900`) accessed
   cyclically, three times each.
2. **Streaming phase:** six consecutive blocks (`0x1000`–`0x1140`), then five of
   them accessed again.

The trace touches **9 distinct blocks**, so at least 9 accesses must miss
(compulsory misses) and the best possible hit rate is **11/20 = 55%**.

| Configuration      | Hits | Misses | Hit Rate | Compulsory | Conflict | Capacity |
| :----------------- | ---: | -----: | -------: | ---------: | -------: | -------: |
| 1 KB, direct-mapped |    5 |     15 |    25.0% |          9 |        6 |        0 |
| 1 KB, 2-way         |    5 |     15 |    25.0% |          9 |        6 |        0 |
| 2 KB, direct-mapped |    7 |     13 |    35.0% |          9 |        4 |        0 |
| **1 KB, 4-way**     | **11** | **9** | **55.0%** |       9 |    **0** |        0 |

### What the results show

**The workload is conflict-bound, not capacity-bound.** The working set is
9 blocks, and a 1 KB cache holds 16, so the data always fits; there are no
capacity misses in any configuration. All the extra misses come from the way
addresses are mapped to sets.

- **Direct-mapped (1 KB):** `0x100`, `0x500` and `0x900` all decode to set 4.
  With only one way, each access evicts the block that is needed next, so the
  whole ping-pong phase misses.
- **2-way (1 KB):** No improvement. The three blocks still share one set, and
  cycling three blocks through two ways is the worst case for LRU: the block
  evicted is always the one requested next.
- **Direct-mapped (2 KB):** Doubling capacity adds an index bit, which moves
  `0x500` into its own set. It now hits on reuse, but `0x100` and `0x900`
  still collide. The gain comes from the different mapping, not from the
  extra space.
- **4-way (1 KB):** With enough ways to hold all three conflicting blocks,
  every conflict miss disappears and the cache reaches the 55% optimum at
  **half the size** of the 2 KB configuration.

**Takeaway:** For this access pattern, adding associativity is worth more than
adding capacity, as long as there are enough ways to cover the number of hot
blocks that share a set. The 2-way result is a reminder that LRU breaks down
whenever a cyclic working set is even one block larger than the
associativity.## Architectural Analysis Results

The simulator was used to compare cache configurations on a small synthetic
workload (`test.trace`, 20 accesses, 64-byte blocks). The trace has two phases:

1. **Ping-pong phase:** three addresses (`0x100`, `0x500`, `0x900`) accessed
   cyclically, three times each.
2. **Streaming phase:** six consecutive blocks (`0x1000`–`0x1140`), then five of
   them accessed again.

The trace touches **9 distinct blocks**, so at least 9 accesses must miss
(compulsory misses) and the best possible hit rate is **11/20 = 55%**.

| Configuration      | Hits | Misses | Hit Rate | Compulsory | Conflict | Capacity |
| :----------------- | ---: | -----: | -------: | ---------: | -------: | -------: |
| 1 KB, direct-mapped |    5 |     15 |    25.0% |          9 |        6 |        0 |
| 1 KB, 2-way         |    5 |     15 |    25.0% |          9 |        6 |        0 |
| 2 KB, direct-mapped |    7 |     13 |    35.0% |          9 |        4 |        0 |
| **1 KB, 4-way**     | **11** | **9** | **55.0%** |       9 |    **0** |        0 |

### What the results show

**The workload is conflict-bound, not capacity-bound.** The working set is
9 blocks, and a 1 KB cache holds 16, so the data always fits; there are no
capacity misses in any configuration. All the extra misses come from the way
addresses are mapped to sets.

- **Direct-mapped (1 KB):** `0x100`, `0x500` and `0x900` all decode to set 4.
  With only one way, each access evicts the block that is needed next, so the
  whole ping-pong phase misses.
- **2-way (1 KB):** No improvement. The three blocks still share one set, and
  cycling three blocks through two ways is the worst case for LRU: the block
  evicted is always the one requested next.
- **Direct-mapped (2 KB):** Doubling capacity adds an index bit, which moves
  `0x500` into its own set. It now hits on reuse, but `0x100` and `0x900`
  still collide. The gain comes from the different mapping, not from the
  extra space.
- **4-way (1 KB):** With enough ways to hold all three conflicting blocks,
  every conflict miss disappears and the cache reaches the 55% optimum at
  **half the size** of the 2 KB configuration.

**Takeaway:** For this access pattern, adding associativity is worth more than
adding capacity, as long as there are enough ways to cover the number of hot
blocks that share a set. The 2-way result is a reminder that LRU breaks down
whenever a cyclic working set is even one block larger than the
associativity.## Architectural Analysis Results

The simulator was used to compare cache configurations on a small synthetic
workload (`test.trace`, 20 accesses, 64-byte blocks). The trace has two phases:

1. **Ping-pong phase:** three addresses (`0x100`, `0x500`, `0x900`) accessed
   cyclically, three times each.
2. **Streaming phase:** six consecutive blocks (`0x1000`–`0x1140`), then five of
   them accessed again.

The trace touches **9 distinct blocks**, so at least 9 accesses must miss
(compulsory misses) and the best possible hit rate is **11/20 = 55%**.

| Configuration      | Hits | Misses | Hit Rate | Compulsory | Conflict | Capacity |
| :----------------- | ---: | -----: | -------: | ---------: | -------: | -------: |
| 1 KB, direct-mapped |    5 |     15 |    25.0% |          9 |        6 |        0 |
| 1 KB, 2-way         |    5 |     15 |    25.0% |          9 |        6 |        0 |
| 2 KB, direct-mapped |    7 |     13 |    35.0% |          9 |        4 |        0 |
| **1 KB, 4-way**     | **11** | **9** | **55.0%** |       9 |    **0** |        0 |

### What the results show

**The workload is conflict-bound, not capacity-bound.** The working set is
9 blocks, and a 1 KB cache holds 16, so the data always fits; there are no
capacity misses in any configuration. All the extra misses come from the way
addresses are mapped to sets.

- **Direct-mapped (1 KB):** `0x100`, `0x500` and `0x900` all decode to set 4.
  With only one way, each access evicts the block that is needed next, so the
  whole ping-pong phase misses.
- **2-way (1 KB):** No improvement. The three blocks still share one set, and
  cycling three blocks through two ways is the worst case for LRU: the block
  evicted is always the one requested next.
- **Direct-mapped (2 KB):** Doubling capacity adds an index bit, which moves
  `0x500` into its own set. It now hits on reuse, but `0x100` and `0x900`
  still collide. The gain comes from the different mapping, not from the
  extra space.
- **4-way (1 KB):** With enough ways to hold all three conflicting blocks,
  every conflict miss disappears and the cache reaches the 55% optimum at
  **half the size** of the 2 KB configuration.

**Takeaway:** For this access pattern, adding associativity is worth more than
adding capacity, as long as there are enough ways to cover the number of hot
blocks that share a set. The 2-way result is a reminder that LRU breaks down
whenever a cyclic working set is even one block larger than the
associativity.