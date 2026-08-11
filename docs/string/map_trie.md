---
title: Map Trie
documentation_of: ../../string/map_trie.hpp
---

## Overview

`m1une::string::MapTrie` is a multiset trie whose outgoing edges are stored in
`std::map`. It is useful when symbols come from a large, sparse, or non-integral
alphabet for which allocating one transition per possible symbol is wasteful.

It supports duplicate insertion, deletion, exact lookup, prefix counting, and
enumerating stored sequences that are prefixes of a query. Nodes are kept in a
contiguous vector, while each node allocates only the transitions it uses.

## Template Parameters

* `Symbol`: Key type stored on each edge.
* `Compare`: Strict weak ordering for `Symbol`. Defaults to
  `std::less<Symbol>` and must be default-constructible.

The input to an operation may be any iterable sequence whose elements can be
used to search for and construct `Symbol` values. Examples include strings,
integer vectors, and vectors of coordinate pairs with a suitable comparator.

## Methods

For a sequence of length $L$, let $d_i$ be the number of outgoing transitions
at the node visited before its $i$-th symbol, and let $K$ be the allocated node
count. The bounds below assume that comparing two symbols takes $O(1)$ time;
otherwise, multiply the logarithmic terms by the comparison cost.

| Method | Description | Complexity |
| --- | --- | --- |
| `MapTrie()` | Constructs an empty trie. | $O(1)$ |
| `int size() const` | Returns the number of stored sequences including duplicates. | $O(1)$ |
| `int distinct_size() const` | Returns the number of distinct stored sequences. | $O(1)$ |
| `bool empty() const` | Returns whether no sequences are stored. | $O(1)$ |
| `node_id root() const` | Returns the root node handle. | $O(1)$ |
| `node_id find(const Sequence& sequence) const` | Returns the node reached by an active path, or `null_node` if absent. | $O(\sum_i \log(d_i + 1))$ |
| `const Node& node(node_id id) const` | Returns a read-only node view. | $O(1)$ |
| `size_t node_count() const` | Returns allocated nodes, including the root. | $O(1)$ |
| `void reserve(size_t n)` | Reserves vector storage for approximately `n` nodes. | $O(K)$ |
| `void clear()` | Removes all sequences and returns to one root node. | $O(K)$ |
| `node_id insert(const Sequence& sequence, int multiplicity = 1)` | Inserts copies and returns the endpoint node handle. | $O(\sum_i \log(d_i + 1))$ |
| `int count(const Sequence& sequence) const` | Returns the sequence multiplicity. | $O(\sum_i \log(d_i + 1))$ |
| `bool contains(const Sequence& sequence) const` | Returns whether the sequence is stored. | $O(\sum_i \log(d_i + 1))$ |
| `int prefix_count(const Sequence& prefix) const` | Counts stored sequences beginning with `prefix`, including duplicates. | $O(\sum_i \log(d_i + 1))$ |
| `bool starts_with(const Sequence& prefix) const` | Returns whether a stored sequence begins with `prefix`. | $O(\sum_i \log(d_i + 1))$ |
| `bool erase_one(const Sequence& sequence)`, `bool erase(const Sequence& sequence)` | Erases one copy and reports success. | $O(\sum_i \log(d_i + 1))$ |
| `int erase_all(const Sequence& sequence)` | Erases all copies and returns the number erased. | $O(\sum_i \log(d_i + 1))$ |
| `void for_each_prefix(const Sequence& sequence, Callback callback) const` | Calls `callback(length, multiplicity)` for every stored prefix. | $O(\sum_i \log(d_i + 1))$ plus callback time |
| `int longest_prefix(const Sequence& sequence) const` | Returns the longest stored prefix length, or `-1` if none exists. | $O(\sum_i \log(d_i + 1))$ |

Each `Node` exposes `child`, `subtree_count`, and `terminal_count`. The `child`
member has type `std::map<Symbol, node_id, Compare>`. Node handles remain valid
across insertions and erasures and may index user-owned metadata. References
returned by `node()` can be invalidated by insertion, `reserve()`, or `clear()`.

Erasing does not reclaim nodes or transitions. `clear()` invalidates all old
handles except the root. The empty sequence is supported and is reported by
`for_each_prefix` with length `0` when stored.

For a small contiguous character alphabet, prefer `m1une::string::Trie`: its
array transitions give lower constants and $O(L)$ operations.

## Example

```cpp
#include "string/map_trie.hpp"

#include <iostream>
#include <vector>

int main() {
    m1une::string::MapTrie<int> trie;

    std::vector<int> first;
    first.push_back(1000000000);
    first.push_back(-7);
    std::vector<int> second = first;
    second.push_back(42);

    trie.insert(first, 2);
    trie.insert(second);

    std::cout << trie.count(first) << "\n";        // 2
    std::cout << trie.prefix_count(first) << "\n"; // 3
    std::cout << trie.longest_prefix(second) << "\n"; // 3
}
```
