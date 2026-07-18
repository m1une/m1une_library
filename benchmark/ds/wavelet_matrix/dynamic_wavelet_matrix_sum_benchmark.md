# Dynamic Wavelet Matrix Sum Benchmark

This is a local performance benchmark, not an online-judge verification target.
It models 100,000 initial elements followed by 100,000 operations. Every
operation performs one replacement and one `max_count_largest` query. Initial
and replacement values are generated in advance, coordinate-compressed, and
stored in `DynamicWaveletMatrixSum<uint32_t, long long, 18>` with the original
values as weights.

The workload mixes short, medium, and full-array intervals; repeatedly updated
positions; unchanged and substantially changed keys; and reachable and
unreachable thresholds. The executable reports construction, accumulated
replacement, accumulated query, total elapsed time, peak resident memory, a
checksum, and optional internal counters. It has no `PROBLEM` metadata and is
not registered with `oj-verify`.

## Reproduction

Measurements below used:

- Apple M1 Pro, 10 cores, 16 GB memory, arm64
- Homebrew GCC 16.1.0
- `-std=c++20 -O2 -DNDEBUG -Wall -Wextra -I.`

Compile and run:

```sh
/opt/homebrew/bin/g++-16 -std=c++20 -O2 -DNDEBUG -Wall -Wextra -I. benchmark/ds/wavelet_matrix/dynamic_wavelet_matrix_sum_benchmark.cpp -o /tmp/dwm_sum_benchmark
/tmp/dwm_sum_benchmark
```

The default arguments are `N = 100000` and `Q = 100000`. Smaller runs can pass
`N Q` as command-line arguments. Timings vary with system load; the checksum
must remain `1112562141730900940` for the default deterministic workload.

## Optimization stages

| Stage | Retained change | Construction | Replacement | Query | Total |
| --- | --- | ---: | ---: | ---: | ---: |
| 0 | Original full-width parallel trees, 256/32 chunks | 34 ms | 8953 ms | 2708 ms | 11699 ms |
| 1 | Reduced unsigned key width (`BitWidth = 18`) | 28 ms | 4900 ms | 1438 ms | 6369 ms |
| 2 | Weight chunks tuned to 128/16 for the parallel layout | 25 ms | 4032 ms | 1420 ms | 5480 ms |
| 3 | Delta maintenance for point weight replacement | 25 ms | 3986 ms | 1419 ms | 5434 ms |
| 4 | Fused bit access/rank/insertion/erasure | 27 ms | 3115 ms | 1349 ms | 4494 ms |
| 5 | One-traversal weight erasure | 27 ms | 3009 ms | 1356 ms | 4395 ms |
| 6 | Erasure reconstructs the key and weight; no preliminary access | 27 ms | 3148 ms | 1384 ms | 4562 ms |
| 7 | Shared range-rank traversal | 27 ms | 3024 ms | 1167 ms | 4221 ms |
| 8 | Integrated weighted/rank levels, retuned to 64/16 | 25 ms | 2671 ms | 954 ms | 3653 ms |

Stage 6 reasonably maintained performance but was slightly slower in this
mixture because one seventh of replacements deliberately preserves the key;
the old equality fast path helped those operations after paying for a full-key
access. Removing that preliminary access simplifies the common changed-key
path and enables the integrated stage.

The largest individual reduction came from using the known 18-bit compressed
key width. Fused bit operations then removed multiple root-to-leaf walks per
level. Integrating routing bits and weights removed the remaining parallel-tree
walk and produced the best final replacement and query times.

## Chunk tuning

The parallel-tree Stage 2 sweep was:

| Chunk/group | Replacement | Query | Total | Peak memory |
| --- | ---: | ---: | ---: | ---: |
| 32/8 | 4325 ms | 1827 ms | 6184 ms | 53.3 MiB |
| 64/8 | 4086 ms | 1650 ms | 5765 ms | 47.3 MiB |
| 64/16 | 4079 ms | 1630 ms | 5739 ms | 45.6 MiB |
| 128/16 | 3908 ms | 1382 ms | 5320 ms | 44.5 MiB |

After integration, the same sweep changed the tradeoff:

| Chunk/group | Replacement | Query | Total | Peak memory |
| --- | ---: | ---: | ---: | ---: |
| 32/8 | 2888 ms | 1231 ms | 4149 ms | 47.0 MiB |
| 64/8 | 2966 ms | 1063 ms | 4058 ms | 44.4 MiB |
| 64/16 | 2821 ms | 1025 ms | 3874 ms | 41.3 MiB |
| 128/16 | 3665 ms | 954 ms | 4647 ms | 40.2 MiB |

The final 64/16 layout gives the best mixed-workload time. Its query time is
within eight percent of 128/16 while avoiding the much larger local shift and
rebuild cost during replacement.

## Instrumentation

Counters were reset after construction. The original full-width run and final
integrated run reported:

| Counter | Original | Final integrated |
| --- | ---: | ---: |
| Bitvector tree traversals | 30,171,136 | 0 |
| Weight/integrated tree traversals | 15,928,416 | 5,689,520 |
| Chunk splits | 31,454 | 43,774 |
| Chunk merges | 20,144 | 28,293 |
| Local element/bit moves | 1,219,880,938 | 85,696,960 |
| Full weight-chunk rebuilds | 6,376,325 | 3,963,795 |

The smaller final chunks split and merge more often, but reduce local moves by
more than an order of magnitude. Production instrumentation is compiled out
unless `M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_PROFILE` is defined.

## Complexity and limitations

Construction is `O(BitWidth * N)`. Replacement is expected amortized
`O(BitWidth * log N)`, and threshold queries are expected
`O(BitWidth * log N)`. Memory is `O(BitWidth * N)`.

Insertion and erasure still shift and rebuild one local chunk at each visited
level. The stable final-order weight sequence is also retained because boundary
search inside an equal-key group must preserve sequence order for `smallest`
and reverse sequence order for `largest`. Full-width 64-bit keys therefore cost
proportionally more time and memory than compressed 18-bit keys. Treap height is
expected rather than worst-case deterministic.
