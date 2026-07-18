# Offline Point-Update Range Order-Statistics Benchmark

This is a standalone local benchmark, not formal verification. It compares the
offline-registered value-segment-tree/Fenwick structure with the existing
chunked implicit-treap `DynamicWaveletMatrixSum<uint32_t, long long, 18>`.

The deterministic default workload uses `N = 100000` and `Q = 100000`. All
candidate `(position, key)` states are generated before construction. Each
operation performs one key-and-weight replacement followed by one direct
minimum-count largest-sum threshold query. Intervals mix short random ranges,
arbitrary random ranges, and the full array. Values contain duplicates, some
positions are repeatedly updated, and thresholds mix reachable, immediately
reachable, and unreachable cases.

## Environment and command

- Apple M1 Pro, 10 cores, 16 GB memory, arm64
- Homebrew GCC 16.1.0
- `-std=c++20 -O2 -DNDEBUG -Wall -Wextra -Wconversion -I.`

```sh
/opt/homebrew/bin/g++-16 -std=c++20 -O2 -DNDEBUG -Wall -Wextra -Wconversion -I. benchmark/ds/range_query/offline_point_update_range_order_statistics_sum_benchmark.cpp -o /tmp/offline_order_benchmark
/tmp/offline_order_benchmark
```

Optional `N Q` command-line arguments run a smaller workload.

## Results

The default run registered 112,500 candidate entries before internal
deduplication. Both structures produced checksum `8514932933488690905`.

| Measurement | Offline-registered | Dynamic wavelet matrix |
| --- | ---: | ---: |
| Candidate preparation | 2.943 ms | N/A |
| Construction | 294.003 ms | 24.099 ms |
| Initial activation within construction | 45.129 ms | Included above |
| 100,000 updates | 188.583 ms | 2878.067 ms |
| 100,000 threshold queries | 196.936 ms | 1071.750 ms |
| Total structure time | 682.552 ms | 3977.181 ms |

Peak resident memory for the complete comparison process was 137.906 MiB. The
peak occurs during offline construction, when temporary registration vectors
coexist with the final flat arrays.

The offline structure is about 15 times faster for updates and five times
faster for this threshold query workload, but its construction is roughly
12 times slower and it must retain `O(MH)` registered-state storage. These are
local measurements, not online-judge verification results.
