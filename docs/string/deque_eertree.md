---
title: Deque Eertree
documentation_of: ../../string/deque_eertree.hpp
---

## Overview

`DequeEertree` maintains the palindromic substrings of a sequence while symbols
are inserted or removed at either end. It can report the number of distinct
nonempty palindromes and the longest palindromic prefix and suffix after every
operation.

The implementation records palindrome surfaces and uses quick suffix links.
Its transition arrays require a contiguous, fixed alphabet. The default
alphabet is the lowercase English letters.

`DoubleEndedEertree` and `DequePalindromicTree` are aliases for
`DequeEertree`.

## Template Parameters

- `AlphabetSize`: number of symbols, default `26`.
- `FirstCharacter`: character code mapped to transition zero, default `'a'`.

For example, `DequeEertree<10, '0'>` accepts decimal digits.

## Methods

Let `N` be the current sequence length and let `Q` be the total number of push
operations since the last `clear()`.

| Method | Description | Complexity |
| --- | --- | --- |
| `DequeEertree()` | Creates an empty structure. | `O(1)` |
| `DequeEertree(sequence)` | Builds a structure by pushing the sequence at the back. | `O(N * AlphabetSize)` total |
| `int size() const` | Returns the number of distinct nonempty palindromic substrings. | `O(1)` |
| `int text_length() const` | Returns `N`. | `O(1)` |
| `bool empty() const` | Returns whether the sequence is empty. | `O(1)` |
| `int distinct_palindrome_count() const` | Returns the number of distinct nonempty palindromic substrings. | `O(1)` |
| `int longest_prefix_length() const` | Returns the longest palindromic prefix length, or zero if empty. | `O(1)` |
| `int longest_suffix_length() const` | Returns the longest palindromic suffix length, or zero if empty. | `O(1)` |
| `void reserve(operation_capacity)` | Reserves node storage for future pushes. | `O(Q * AlphabetSize)` if reallocated |
| `void clear()` | Removes the sequence and all historical nodes. | `O(N + Q)` |
| `void push_front(symbol)` | Inserts a symbol at the front. | Amortized `O(AlphabetSize)` |
| `void push_back(symbol)` | Inserts a symbol at the back. | Amortized `O(AlphabetSize)` |
| `void pop_front()` | Removes the front symbol; the sequence must be nonempty. | Amortized `O(1)` |
| `void pop_back()` | Removes the back symbol; the sequence must be nonempty. | Amortized `O(1)` |
| `void build(sequence)` | Pushes every symbol at the back. | `O(N * AlphabetSize)` total |

For a constant alphabet, all deque operations take amortized `O(1)` time. The
structure uses `O(N + Q * AlphabetSize)` memory: deleted historical nodes are
kept so internal node references remain stable. Calling `clear()` discards
those historical nodes, while allocated vector capacity may be retained.

`pop_front()` and `pop_back()` assert when called on an empty sequence. Symbols
outside the configured alphabet also cause an assertion failure.

## Example

```cpp
#include "string/deque_eertree.hpp"
#include <iostream>

int main() {
    m1une::string::DequeEertree<> tree;
    tree.push_back('a');
    tree.push_back('b');
    tree.push_front('b');  // "bab"

    std::cout << tree.distinct_palindrome_count() << '\n';  // 3
    std::cout << tree.longest_prefix_length() << '\n';      // 3
    std::cout << tree.longest_suffix_length() << '\n';      // 3

    tree.pop_front();  // "ab"
    std::cout << tree.distinct_palindrome_count() << '\n';  // 2
}
```
