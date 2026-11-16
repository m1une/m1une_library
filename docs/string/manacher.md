---
title: Manacher Algorithm
documentation_of: ../../string/manacher.hpp
---

## Overview

`manacher(sequence)` finds every maximal odd- and even-length palindrome in
linear time. The result also answers whether any substring is a palindrome in
$O(1)$.

The function is generic over indexable sequences with comparable elements.

## Function

| Function | Description | Complexity |
| --- | --- | --- |
| `template <class Sequence> ManacherResult manacher(const Sequence& sequence)` | Builds odd and even palindrome radii. Elements need equality comparison, `int size() const`, and indexed access. | $O(N)$ time and space, where `N = sequence.size()`. |

An empty input is supported. `is_palindrome(l, r)` accepts
`0 <= l <= r <= N`; the empty substring is a palindrome.

## Result

`ManacherResult` contains:

| Member / Method | Meaning | Complexity |
| --- | --- | --- |
| `odd[i]` | Radius including center `i`; palindrome `[i - odd[i] + 1, i + odd[i])`. | Access $O(1)$ |
| `even[i]` | Radius centered between `i - 1` and `i`; palindrome `[i - even[i], i + even[i])`. | Access $O(1)$ |
| `int size() const` | Returns the original sequence length. | $O(1)$ |
| `bool empty() const` | Returns whether the sequence is empty. | $O(1)$ |
| `bool is_palindrome(int left, int right) const` | Returns whether `[l, r)` is a palindrome. | $O(1)$ |
| `int longest_length() const` | Returns the longest palindromic substring length. | $O(N)$ |

Construction takes $O(N)$ time and space.

## Example

```cpp
#include "string/manacher.hpp"

#include <iostream>
#include <string>

int main() {
    auto palindromes = m1une::string::manacher(std::string("abacaba"));

    std::cout << palindromes.longest_length() << "\n";      // 7
    std::cout << palindromes.is_palindrome(1, 6) << "\n";   // 1
    std::cout << palindromes.is_palindrome(0, 4) << "\n";   // 0
}
```
