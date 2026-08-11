---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/map_trie.test.cpp
    title: verify/string/map_trie.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/map_trie.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstddef>\n#include <functional>\n#include <limits>\n#include <map>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace string {\n\n// A multiset trie whose\
    \ outgoing edges are stored in ordered maps.\ntemplate <class Symbol, class Compare\
    \ = std::less<Symbol>>\nstruct MapTrie {\n    using node_id = int;\n    static\
    \ constexpr node_id null_node = -1;\n\n    struct Node {\n        std::map<Symbol,\
    \ node_id, Compare> child;\n        int subtree_count = 0;\n        int terminal_count\
    \ = 0;\n    };\n\n   private:\n    std::vector<Node> _nodes;\n    int _distinct_size;\n\
    \n    node_id new_node() {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back();\n        return int(_nodes.size()) - 1;\n    }\n\
    \n    template <class Sequence>\n    node_id find_node(const Sequence& sequence)\
    \ const {\n        node_id node = 0;\n        for (const auto& symbol : sequence)\
    \ {\n            auto iterator = _nodes[node].child.find(symbol);\n          \
    \  if (iterator == _nodes[node].child.end()) return null_node;\n            node\
    \ = iterator->second;\n            if (_nodes[node].subtree_count == 0) return\
    \ null_node;\n        }\n        return node;\n    }\n\n   public:\n    MapTrie()\
    \ : _nodes(1), _distinct_size(0) {}\n\n    int size() const {\n        return\
    \ _nodes[0].subtree_count;\n    }\n\n    int distinct_size() const {\n       \
    \ return _distinct_size;\n    }\n\n    bool empty() const {\n        return size()\
    \ == 0;\n    }\n\n    node_id root() const {\n        return 0;\n    }\n\n   \
    \ const Node& node(node_id id) const {\n        assert(0 <= id && std::size_t(id)\
    \ < _nodes.size());\n        return _nodes[id];\n    }\n\n    template <class\
    \ Sequence>\n    node_id find(const Sequence& sequence) const {\n        return\
    \ find_node(sequence);\n    }\n\n    std::size_t node_count() const {\n      \
    \  return _nodes.size();\n    }\n\n    void reserve(std::size_t node_capacity)\
    \ {\n        _nodes.reserve(node_capacity);\n    }\n\n    void clear() {\n   \
    \     _nodes.clear();\n        _nodes.emplace_back();\n        _distinct_size\
    \ = 0;\n    }\n\n    template <class Sequence>\n    node_id insert(const Sequence&\
    \ sequence, int multiplicity = 1) {\n        assert(0 < multiplicity);\n     \
    \   node_id node = 0;\n        _nodes[node].subtree_count += multiplicity;\n \
    \       for (const auto& symbol : sequence) {\n            auto iterator = _nodes[node].child.find(symbol);\n\
    \            node_id child;\n            if (iterator == _nodes[node].child.end())\
    \ {\n                child = new_node();\n                _nodes[node].child.emplace(symbol,\
    \ child);\n            } else {\n                child = iterator->second;\n \
    \           }\n            node = child;\n            _nodes[node].subtree_count\
    \ += multiplicity;\n        }\n        if (_nodes[node].terminal_count == 0) _distinct_size++;\n\
    \        _nodes[node].terminal_count += multiplicity;\n        return node;\n\
    \    }\n\n    template <class Sequence>\n    int count(const Sequence& sequence)\
    \ const {\n        node_id node = find_node(sequence);\n        return node ==\
    \ null_node ? 0 : _nodes[node].terminal_count;\n    }\n\n    template <class Sequence>\n\
    \    bool contains(const Sequence& sequence) const {\n        return count(sequence)\
    \ != 0;\n    }\n\n    // Returns the number of stored sequences beginning with\
    \ prefix.\n    template <class Sequence>\n    int prefix_count(const Sequence&\
    \ prefix) const {\n        node_id node = find_node(prefix);\n        return node\
    \ == null_node ? 0 : _nodes[node].subtree_count;\n    }\n\n    template <class\
    \ Sequence>\n    bool starts_with(const Sequence& prefix) const {\n        return\
    \ prefix_count(prefix) != 0;\n    }\n\n    template <class Sequence>\n    bool\
    \ erase_one(const Sequence& sequence) {\n        node_id terminal = find_node(sequence);\n\
    \        if (terminal == null_node || _nodes[terminal].terminal_count == 0) {\n\
    \            return false;\n        }\n\n        node_id node = 0;\n        _nodes[node].subtree_count--;\n\
    \        for (const auto& symbol : sequence) {\n            node = _nodes[node].child.find(symbol)->second;\n\
    \            _nodes[node].subtree_count--;\n        }\n        _nodes[node].terminal_count--;\n\
    \        if (_nodes[node].terminal_count == 0) _distinct_size--;\n        return\
    \ true;\n    }\n\n    template <class Sequence>\n    bool erase(const Sequence&\
    \ sequence) {\n        return erase_one(sequence);\n    }\n\n    template <class\
    \ Sequence>\n    int erase_all(const Sequence& sequence) {\n        int multiplicity\
    \ = count(sequence);\n        if (multiplicity == 0) return 0;\n\n        node_id\
    \ node = 0;\n        _nodes[node].subtree_count -= multiplicity;\n        for\
    \ (const auto& symbol : sequence) {\n            node = _nodes[node].child.find(symbol)->second;\n\
    \            _nodes[node].subtree_count -= multiplicity;\n        }\n        _nodes[node].terminal_count\
    \ = 0;\n        _distinct_size--;\n        return multiplicity;\n    }\n\n   \
    \ // Calls callback(length, multiplicity) for every stored prefix.\n    // The\
    \ empty prefix is reported with length 0 when it is stored.\n    template <class\
    \ Sequence, class Callback>\n    void for_each_prefix(const Sequence& sequence,\
    \ Callback callback) const {\n        node_id node = 0;\n        if (_nodes[node].terminal_count\
    \ != 0) {\n            callback(0, _nodes[node].terminal_count);\n        }\n\n\
    \        int length = 0;\n        for (const auto& symbol : sequence) {\n    \
    \        auto iterator = _nodes[node].child.find(symbol);\n            if (iterator\
    \ == _nodes[node].child.end()) return;\n            node = iterator->second;\n\
    \            if (_nodes[node].subtree_count == 0) return;\n            length++;\n\
    \            if (_nodes[node].terminal_count != 0) {\n                callback(length,\
    \ _nodes[node].terminal_count);\n            }\n        }\n    }\n\n    // Returns\
    \ the length of the longest stored sequence that is a prefix.\n    // Returns\
    \ -1 when no stored prefix exists.\n    template <class Sequence>\n    int longest_prefix(const\
    \ Sequence& sequence) const {\n        int result = _nodes[0].terminal_count ==\
    \ 0 ? -1 : 0;\n        for_each_prefix(sequence, [&result](int length, int) {\n\
    \            result = length;\n        });\n        return result;\n    }\n};\n\
    \n}  // namespace string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_MAP_TRIE_HPP\n#define M1UNE_STRING_MAP_TRIE_HPP 1\n\n\
    #include <cassert>\n#include <cstddef>\n#include <functional>\n#include <limits>\n\
    #include <map>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\n\
    // A multiset trie whose outgoing edges are stored in ordered maps.\ntemplate\
    \ <class Symbol, class Compare = std::less<Symbol>>\nstruct MapTrie {\n    using\
    \ node_id = int;\n    static constexpr node_id null_node = -1;\n\n    struct Node\
    \ {\n        std::map<Symbol, node_id, Compare> child;\n        int subtree_count\
    \ = 0;\n        int terminal_count = 0;\n    };\n\n   private:\n    std::vector<Node>\
    \ _nodes;\n    int _distinct_size;\n\n    node_id new_node() {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _nodes.emplace_back();\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    template <class Sequence>\n\
    \    node_id find_node(const Sequence& sequence) const {\n        node_id node\
    \ = 0;\n        for (const auto& symbol : sequence) {\n            auto iterator\
    \ = _nodes[node].child.find(symbol);\n            if (iterator == _nodes[node].child.end())\
    \ return null_node;\n            node = iterator->second;\n            if (_nodes[node].subtree_count\
    \ == 0) return null_node;\n        }\n        return node;\n    }\n\n   public:\n\
    \    MapTrie() : _nodes(1), _distinct_size(0) {}\n\n    int size() const {\n \
    \       return _nodes[0].subtree_count;\n    }\n\n    int distinct_size() const\
    \ {\n        return _distinct_size;\n    }\n\n    bool empty() const {\n     \
    \   return size() == 0;\n    }\n\n    node_id root() const {\n        return 0;\n\
    \    }\n\n    const Node& node(node_id id) const {\n        assert(0 <= id &&\
    \ std::size_t(id) < _nodes.size());\n        return _nodes[id];\n    }\n\n   \
    \ template <class Sequence>\n    node_id find(const Sequence& sequence) const\
    \ {\n        return find_node(sequence);\n    }\n\n    std::size_t node_count()\
    \ const {\n        return _nodes.size();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _nodes.reserve(node_capacity);\n    }\n\n    void\
    \ clear() {\n        _nodes.clear();\n        _nodes.emplace_back();\n       \
    \ _distinct_size = 0;\n    }\n\n    template <class Sequence>\n    node_id insert(const\
    \ Sequence& sequence, int multiplicity = 1) {\n        assert(0 < multiplicity);\n\
    \        node_id node = 0;\n        _nodes[node].subtree_count += multiplicity;\n\
    \        for (const auto& symbol : sequence) {\n            auto iterator = _nodes[node].child.find(symbol);\n\
    \            node_id child;\n            if (iterator == _nodes[node].child.end())\
    \ {\n                child = new_node();\n                _nodes[node].child.emplace(symbol,\
    \ child);\n            } else {\n                child = iterator->second;\n \
    \           }\n            node = child;\n            _nodes[node].subtree_count\
    \ += multiplicity;\n        }\n        if (_nodes[node].terminal_count == 0) _distinct_size++;\n\
    \        _nodes[node].terminal_count += multiplicity;\n        return node;\n\
    \    }\n\n    template <class Sequence>\n    int count(const Sequence& sequence)\
    \ const {\n        node_id node = find_node(sequence);\n        return node ==\
    \ null_node ? 0 : _nodes[node].terminal_count;\n    }\n\n    template <class Sequence>\n\
    \    bool contains(const Sequence& sequence) const {\n        return count(sequence)\
    \ != 0;\n    }\n\n    // Returns the number of stored sequences beginning with\
    \ prefix.\n    template <class Sequence>\n    int prefix_count(const Sequence&\
    \ prefix) const {\n        node_id node = find_node(prefix);\n        return node\
    \ == null_node ? 0 : _nodes[node].subtree_count;\n    }\n\n    template <class\
    \ Sequence>\n    bool starts_with(const Sequence& prefix) const {\n        return\
    \ prefix_count(prefix) != 0;\n    }\n\n    template <class Sequence>\n    bool\
    \ erase_one(const Sequence& sequence) {\n        node_id terminal = find_node(sequence);\n\
    \        if (terminal == null_node || _nodes[terminal].terminal_count == 0) {\n\
    \            return false;\n        }\n\n        node_id node = 0;\n        _nodes[node].subtree_count--;\n\
    \        for (const auto& symbol : sequence) {\n            node = _nodes[node].child.find(symbol)->second;\n\
    \            _nodes[node].subtree_count--;\n        }\n        _nodes[node].terminal_count--;\n\
    \        if (_nodes[node].terminal_count == 0) _distinct_size--;\n        return\
    \ true;\n    }\n\n    template <class Sequence>\n    bool erase(const Sequence&\
    \ sequence) {\n        return erase_one(sequence);\n    }\n\n    template <class\
    \ Sequence>\n    int erase_all(const Sequence& sequence) {\n        int multiplicity\
    \ = count(sequence);\n        if (multiplicity == 0) return 0;\n\n        node_id\
    \ node = 0;\n        _nodes[node].subtree_count -= multiplicity;\n        for\
    \ (const auto& symbol : sequence) {\n            node = _nodes[node].child.find(symbol)->second;\n\
    \            _nodes[node].subtree_count -= multiplicity;\n        }\n        _nodes[node].terminal_count\
    \ = 0;\n        _distinct_size--;\n        return multiplicity;\n    }\n\n   \
    \ // Calls callback(length, multiplicity) for every stored prefix.\n    // The\
    \ empty prefix is reported with length 0 when it is stored.\n    template <class\
    \ Sequence, class Callback>\n    void for_each_prefix(const Sequence& sequence,\
    \ Callback callback) const {\n        node_id node = 0;\n        if (_nodes[node].terminal_count\
    \ != 0) {\n            callback(0, _nodes[node].terminal_count);\n        }\n\n\
    \        int length = 0;\n        for (const auto& symbol : sequence) {\n    \
    \        auto iterator = _nodes[node].child.find(symbol);\n            if (iterator\
    \ == _nodes[node].child.end()) return;\n            node = iterator->second;\n\
    \            if (_nodes[node].subtree_count == 0) return;\n            length++;\n\
    \            if (_nodes[node].terminal_count != 0) {\n                callback(length,\
    \ _nodes[node].terminal_count);\n            }\n        }\n    }\n\n    // Returns\
    \ the length of the longest stored sequence that is a prefix.\n    // Returns\
    \ -1 when no stored prefix exists.\n    template <class Sequence>\n    int longest_prefix(const\
    \ Sequence& sequence) const {\n        int result = _nodes[0].terminal_count ==\
    \ 0 ? -1 : 0;\n        for_each_prefix(sequence, [&result](int length, int) {\n\
    \            result = length;\n        });\n        return result;\n    }\n};\n\
    \n}  // namespace string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_MAP_TRIE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/map_trie.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-08-11 13:50:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/map_trie.test.cpp
  - verify/string/string_algorithms.test.cpp
documentation_of: string/map_trie.hpp
layout: document
title: Map Trie
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
