---
title: Palindrome Lexicographical Order
documentation_of: ../../string/palindrome_lexicographical_order.hpp
---

## Overview

`PalindromeLexicographicalOrder` indexes every distinct nonempty palindromic
substring of one sequence. It assigns zero-based ranks after sorting the
palindromes lexicographically and supports both directions:

- find the rank of a palindrome or eertree node;
- recover the node, a representative occurrence, or a copy of the palindrome
  at a given rank.

The index combines an eertree with a suffix array. It does not count duplicate
occurrences separately.

```cpp
#include "string/palindrome_lexicographical_order.hpp"
```

## Template Parameters

```cpp
template <
    class Sequence = std::string,
    int AlphabetSize = 26,
    int FirstCharacter = 'a'
>
struct PalindromeLexicographicalOrder;
```

`Sequence` must provide `size()`, random-access iterators, and `operator[]`,
and it must be constructible from a pair of its iterators. Its value type must
be convertible to `int` and sortable. Symbols must belong to the contiguous range
`[FirstCharacter, FirstCharacter + AlphabetSize)`.

The default specialization accepts lowercase English strings. For a vector
whose values are in `[0, 4)`, use
`PalindromeLexicographicalOrder<std::vector<int>, 4, 0>`.

## Methods

Let `N` be the sequence length, `D` the number of distinct nonempty
palindromic substrings, and `L` the length of a queried or returned
palindrome.

| Method | Description | Complexity |
| --- | --- | --- |
| `PalindromeLexicographicalOrder()` | Constructs an empty index. | $O(1)$ |
| `PalindromeLexicographicalOrder(sequence)` | Copies or moves the sequence and builds its index. | $O(N \cdot AlphabetSize + N \log N)$ time and $O(N \cdot AlphabetSize)$ memory |
| `int size() const` | Returns `D`. | $O(1)$ |
| `bool empty() const` | Returns whether `D == 0`. | $O(1)$ |
| `int text_length() const` | Returns `N`. | $O(1)$ |
| `const Sequence& sequence() const` | Returns the indexed sequence. | $O(1)$ |
| `const eertree_type& eertree() const` | Returns the underlying eertree. | $O(1)$ |
| `const vector<node_id>& nodes_in_order() const` | Returns all real eertree nodes in increasing lexicographic order. | $O(1)$ |
| `int order_of_node(id) const` | Returns the zero-based rank of a real eertree node. | $O(1)$ |
| `node_id node_by_order(order) const` | Returns the eertree node having the given rank. | $O(1)$ |
| `node_id find(palindrome) const` | Returns its node, or `eertree_type::null_node` if it is not a nonempty palindromic substring. | $O(L)$ |
| `bool contains(palindrome) const` | Tests whether it is indexed. | $O(L)$ |
| `int order_of_palindrome(palindrome) const` | Returns its rank, or `-1` if it is not indexed. | $O(L)$ |
| `pair<int, int> representative_occurrence(order) const` | Returns a half-open occurrence interval of the ranked palindrome. | $O(1)$ |
| `Sequence palindrome(order) const` | Returns a copy of the ranked palindrome. | $O(L)$ |
| `Sequence kth(order) const` | Alias of `palindrome(order)`. | $O(L)$ |

`order_of_node`, `node_by_order`, `representative_occurrence`, `palindrome`,
and `kth` assert that their node or order is valid. The empty string is not
indexed. All query methods are non-mutating.

For a constant alphabet, construction takes $O(N \log N)$ time. It uses
$O(N)$ additional memory outside the fixed transition arrays stored by the
eertree.

## Example

```cpp
#include "string/palindrome_lexicographical_order.hpp"

#include <iostream>
#include <string>

int main() {
    m1une::string::PalindromeLexicographicalOrder<> index(
        std::string("abacaba")
    );

    std::cout << index.order_of_palindrome(std::string("aca")) << '\n';
    for (int order = 0; order < index.size(); order++) {
        std::cout << order << ' ' << index.palindrome(order) << '\n';
    }
}
```
