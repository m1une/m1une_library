---
title: Suffix Tree
documentation_of: ../../string/suffix_tree.hpp
---

## Overview

`SuffixTree` stores all suffixes of a static text in a compact trie. It supports
substring lookup, occurrence counting, representative occurrences, and direct
tree traversal.

Construction uses Ukkonen's algorithm. A unique terminal symbol is appended
internally, so every suffix, including the empty suffix, ends at its own leaf.
The terminal symbol has index `AlphabetSize` and cannot occur in input.

For a fixed alphabet, construction takes `O(N)` time, creates at most
`max(2, 2N + 1)` nodes, and uses `O(N * AlphabetSize)` memory for fixed
transition arrays.

## How to Use the Tree

Node zero is the root. Every non-root node has one incoming edge, and
`node(v).parent` is the node at the other end of that edge. The edge label is
the slice

```cpp
text.substr(tree.node(v).left, tree.edge_length(v))
```

except that a leaf edge may include the internal terminal symbol at position
`text.size()`. In that case `node(v).right == text.size() + 1`; exclude the last
position when reading the label from the original string.

There are two ways to access children:

```cpp
// Follow a known character in O(1).
int child = tree.child(node, 'a');

// Visit only existing children in O(number of children).
tree.for_each_child(node, [&](int symbol, int child) {
    // symbol is 0 for 'a', 1 for 'b', ..., or terminal_symbol.
});
```

`for_each_child` does not scan the alphabet. Each node stores a linked list of
its actual children in ascending symbol order. The same list can be traversed
manually when a callback is inconvenient:

```cpp
for (
    int child = tree.node(node).first_child;
    child != tree.null_node;
    child = tree.node(child).next_sibling
) {
    int symbol = tree.node(child).incoming_symbol;
    // Use child and symbol.
}
```

Concatenating incoming edge labels from the root to a node gives the string
represented by that node. A leaf represents the suffix beginning at
`node(leaf).suffix_start`. `node(v).leaf_count` is the number of occurrences of
the path string of `v`.

Most substring-query code does not need to traverse the topology manually:

```cpp
auto locus = tree.find(pattern);
if (locus) {
    int occurrences = tree.node(locus.node).leaf_count;
}
```

The pattern can end in the middle of an edge. `locus.node` is the child at the
end of that edge, and `locus.offset` is the number of edge symbols consumed.
The descendant leaves—and therefore the occurrence count—are the same for
every point inside that edge.

## Template Parameters

- `AlphabetSize`: number of input symbols, default `26`.
- `FirstCharacter`: character code mapped to transition zero, default `'a'`.

Every input symbol `c` must satisfy
`FirstCharacter <= c < FirstCharacter + AlphabetSize`. For decimal strings,
use `SuffixTree<10, '0'>`.

## Node and Locus Fields

An edge into node `v` is labeled by the internal augmented-text interval
`[node(v).left, node(v).right)`. The augmented text has length `N + 1`; position
`N` is the unique terminal symbol.

| Field | Meaning |
| --- | --- |
| `next[c]` | Child whose edge starts with symbol index `c`, or `null_node`. Index `AlphabetSize` is the terminal symbol. |
| `suffix_link` | Ukkonen suffix link for an internal node. It may be `null_node` for a leaf. |
| `parent` | Parent node, or `null_node` at the root. |
| `left`, `right` | Half-open augmented-text interval labeling the incoming edge. |
| `suffix_start` | Starting position of the represented suffix for a leaf, or `-1` for an internal node. |
| `representative_suffix` | Start of one descendant suffix. |
| `leaf_count` | Number of descendant leaves. |
| `incoming_symbol` | First symbol index of the incoming edge, or `-1` at the root. |
| `first_child` | First actual child in symbol order, or `null_node`. |
| `next_sibling` | Next child of the same parent, or `null_node`. |
| `child_count` | Number of actual children. |

`Locus` contains `node` and `offset`. A successful search may end inside the
incoming edge of `node`; `offset` is the number of consumed symbols on that
edge. It is an explicit node exactly when `offset == edge_length(node)`.
A `Locus` converts to `false` when no match exists.

## Methods

Let `V` be the number of nodes, `L` a query length, and `A = AlphabetSize`.

| Method | Description | Complexity |
| --- | --- | --- |
| `SuffixTree()` | Builds the tree of the empty text and its terminal suffix. | `O(A)` |
| `template<class Sequence> explicit SuffixTree(const Sequence& sequence)` | Builds the suffix tree of `sequence`. | `O(N * A)` |
| `int size() const`, `int node_count() const` | Returns `V`, including the root and terminal leaf. | `O(1)` |
| `bool empty() const` | Returns whether the original text is empty. | `O(1)` |
| `int text_length() const` | Returns `N`, excluding the terminal symbol. | `O(1)` |
| `node_id root() const` | Returns node zero. | `O(1)` |
| `const Node& node(node_id id) const` | Returns node metadata. | `O(1)` |
| `const std::vector<Node>& nodes() const` | Returns all nodes. | `O(1)` |
| `int edge_length(node_id id) const` | Returns the length of the incoming edge. | `O(1)` |
| `bool is_leaf(node_id id) const` | Tests whether a node represents one complete suffix. | `O(1)` |
| `template<class Symbol> node_id child(node_id id, const Symbol& symbol) const` | Returns an input-symbol child, or `null_node`. | `O(1)` |
| `node_id child_by_index(node_id id, int symbol) const` | Returns a child by symbol index, including `terminal_symbol`. | `O(1)` |
| `template<class Callback> void for_each_child(node_id id, Callback callback) const` | Calls `callback(symbol, child)` for each actual child in symbol-index order. | `O(node(id).child_count)` |
| `void clear()` | Replaces the tree with the empty-text tree. | `O(V + A)` |
| `template<class Sequence> void build(const Sequence& sequence)` | Replaces the tree with the suffix tree of `sequence`. | `O(V + N * A)` |
| `template<class Sequence> Locus find(const Sequence& sequence) const` | Returns the locus of a substring, or a false locus. | `O(L)` |
| `template<class Sequence> bool contains(const Sequence& sequence) const` | Tests whether a sequence is a substring. | `O(L)` |
| `template<class Sequence> int count_occurrences(const Sequence& sequence) const` | Counts possibly overlapping occurrences. | `O(L)` |
| `template<class Sequence> std::pair<int, int> representative_occurrence(const Sequence& sequence) const` | Returns one half-open occurrence, or `(-1, -1)`. | `O(L)` |
| `long long distinct_substring_count() const` | Counts distinct nonempty substrings. | `O(V)` |

For the empty query, `count_occurrences` returns `N + 1` and
`representative_occurrence` returns an empty interval.

Node handles remain valid until `build` or `clear`. Both operations rebuild the
whole tree and invalidate all earlier handles and references.

## Example

```cpp
#include "string/suffix_tree.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string text = "ababa";
    m1une::string::SuffixTree<> tree(text);

    std::cout << tree.contains(std::string("bab")) << '\n';       // 1
    std::cout << tree.count_occurrences(std::string("aba")) << '\n';  // 2
    std::cout << tree.distinct_substring_count() << '\n';         // 9

    auto occurrence = tree.representative_occurrence(std::string("bab"));
    std::cout << occurrence.first << ' ' << occurrence.second << '\n';

    // Print every edge as: parent, child, label.
    std::vector<int> stack(1, tree.root());
    while (!stack.empty()) {
        int parent = stack.back();
        stack.pop_back();
        tree.for_each_child(parent, [&](int symbol, int child) {
            const auto& current = tree.node(child);
            int right = std::min(current.right, tree.text_length());
            std::string label = text.substr(current.left, right - current.left);
            std::cout << parent << " -> " << child << ": " << label;
            if (symbol == tree.terminal_symbol || current.right > tree.text_length()) {
                std::cout << '$';
            }
            std::cout << '\n';
            stack.push_back(child);
        });
    }
}
```
