---
title: Algorithms All
documentation_of: ../../algo/all.hpp
---

## Overview

`algo/all.hpp` includes one-shot, domain-neutral algorithms. The public
namespace is `m1une::algo`; subdirectories are only browsing categories.

Convex optimization helpers live under `convex/`.

If a header builds an object and then answers repeated queries, it belongs in
`ds/` instead, even when it is static. For example, cumulative sums live in
`ds/range_query/`.

## Included Headers

| Header | Contents |
| --- | --- |
| `algo/sequence/all.hpp` | Sequence and array algorithms such as LIS, inversion count, non-adjacent selection, run-length encoding, and subset sum. |
| `algo/search/all.hpp` | Search-over-answer and unimodal optimization helpers. |
| `algo/offline/all.hpp` | Offline query processing such as Mo's algorithm. |
| `algo/enumeration/all.hpp` | Combinatorial traversal helpers such as Gray-code enumeration. |
| `algo/dp/all.hpp` | Domain-neutral DP helpers such as knapsack routines. |
