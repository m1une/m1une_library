---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/counting_primes.test.cpp
    title: verify/math/counting_primes.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/enumerate_quotients.test.cpp
    title: verify/math/enumerate_quotients.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/sum_of_multiplicative_function.test.cpp
    title: verify/math/sum_of_multiplicative_function.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/multiplicative_function_prefix_sum.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cmath>\n#include <cstdint>\n#include\
    \ <limits>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ math {\n\n// Computes summatory multiplicative functions with a Min_25 sieve.\n\
    // prime_power(p, e) must return f(p^e), and prime_prefix must contain\n// sum_{p\
    \ <= x} f(p) at every x represented by quotient_values().\ntemplate <class T,\
    \ class PrimePower>\nstruct MultiplicativeFunctionPrefixSum {\n   private:\n \
    \   uint64_t _n;\n    uint64_t _sqrt_n;\n    uint64_t _large_size;\n    std::vector<int>\
    \ _primes;\n    PrimePower _prime_power;\n\n    static uint64_t integer_sqrt(uint64_t\
    \ n) {\n        uint64_t result = static_cast<uint64_t>(std::sqrt(static_cast<long\
    \ double>(n)));\n        while (result != 0 && result > n / result) result--;\n\
    \        while (result + 1 <= n / (result + 1)) result++;\n        return result;\n\
    \    }\n\n    static uint64_t validated_sqrt(uint64_t n) {\n        const uint64_t\
    \ result = integer_sqrt(n);\n        assert(result <= static_cast<uint64_t>(std::numeric_limits<int>::max()\
    \ / 2));\n        return result;\n    }\n\n    static std::vector<int> enumerate_primes(uint64_t\
    \ limit) {\n        assert(limit <= static_cast<uint64_t>(std::numeric_limits<int>::max()));\n\
    \        const int n = static_cast<int>(limit);\n        std::vector<bool> is_composite(n\
    \ + 1);\n        std::vector<int> primes;\n        for (int value = 2; value <=\
    \ n; value++) {\n            if (!is_composite[value]) primes.push_back(value);\n\
    \            for (int prime : primes) {\n                if (value > n / prime)\
    \ break;\n                is_composite[value * prime] = true;\n              \
    \  if (value % prime == 0) break;\n            }\n        }\n        return primes;\n\
    \    }\n\n    T triangular(uint64_t n) const {\n        if ((n & 1) == 0) return\
    \ T(n / 2) * T(n + 1);\n        return T(n) * T((n + 1) / 2);\n    }\n\n   public:\n\
    \    explicit MultiplicativeFunctionPrefixSum(uint64_t n, PrimePower prime_power)\n\
    \        : _n(n),\n          _sqrt_n(validated_sqrt(n)),\n          _large_size(n\
    \ == 0 ? 0 : n / _sqrt_n),\n          _primes(enumerate_primes(_sqrt_n)),\n  \
    \        _prime_power(std::move(prime_power)) {\n        if (n == 0) return;\n\
    \        while (_large_size > 1 && n / (_large_size - 1) == _sqrt_n) _large_size--;\n\
    \    }\n\n    uint64_t n() const {\n        return _n;\n    }\n\n    uint64_t\
    \ sqrt_n() const {\n        return _sqrt_n;\n    }\n\n    const std::vector<int>&\
    \ primes() const {\n        return _primes;\n    }\n\n    int table_size() const\
    \ {\n        if (_n == 0) return 0;\n        return static_cast<int>(_large_size\
    \ + _sqrt_n);\n    }\n\n    // Returns the table index representing x. The argument\
    \ must be one of the\n    // values returned by quotient_values().\n    int index(uint64_t\
    \ x) const {\n        assert(_n > 0 && 1 <= x && x <= _n);\n        if (x <= _sqrt_n)\
    \ return table_size() - static_cast<int>(x);\n        const uint64_t result =\
    \ _n / x;\n        assert(result < _large_size);\n        return static_cast<int>(result);\n\
    \    }\n\n    // table[i] represents the value at quotient_values()[i]. Index\
    \ zero is a\n    // dummy entry; the represented values occupy indices [1, table_size()).\n\
    \    std::vector<uint64_t> quotient_values() const {\n        if (_n == 0) return\
    \ {};\n        std::vector<uint64_t> result(table_size());\n        for (uint64_t\
    \ i = 1; i < _large_size; i++) result[i] = _n / i;\n        for (uint64_t value\
    \ = 1; value <= _sqrt_n; value++) {\n            result[index(value)] = value;\n\
    \        }\n        return result;\n    }\n\n    // Returns pi(x) at every represented\
    \ x.\n    std::vector<T> prime_count_table() const {\n        if (_n == 0) return\
    \ {};\n        std::vector<uint64_t> large(_large_size);\n        for (uint64_t\
    \ i = 1; i < _large_size; i++) large[i] = _n / i - 1;\n\n        std::vector<uint64_t>\
    \ small(_sqrt_n + 1);\n        for (uint64_t value = 1; value <= _sqrt_n; value++)\
    \ small[value] = value - 1;\n\n        uint64_t prime_count = 0;\n        for\
    \ (int prime_int : _primes) {\n            const uint64_t prime = static_cast<uint64_t>(prime_int);\n\
    \            const uint64_t square = prime * prime;\n            const uint64_t\
    \ end = std::min(_large_size, _n / square + 1);\n            uint64_t product\
    \ = prime;\n            for (uint64_t i = 1; i < end; i++, product += prime) {\n\
    \                const uint64_t previous = product < _large_size ? large[product]\
    \ : small[_n / product];\n                large[i] -= previous - prime_count;\n\
    \            }\n            for (uint64_t value = _sqrt_n; value >= square; value--)\
    \ {\n                small[value] -= small[value / prime] - prime_count;\n   \
    \         }\n            prime_count++;\n        }\n\n        std::vector<T> result(table_size());\n\
    \        for (uint64_t i = 0; i < _large_size; i++) result[i] = T(large[i]);\n\
    \        for (uint64_t value = 1; value <= _sqrt_n; value++) result[index(value)]\
    \ = T(small[value]);\n        return result;\n    }\n\n    // Returns sum_{p <=\
    \ x} p at every represented x.\n    std::vector<T> prime_sum_table() const {\n\
    \        if (_n == 0) return {};\n        std::vector<T> result(table_size());\n\
    \        for (uint64_t i = 1; i < _large_size; i++) result[i] = triangular(_n\
    \ / i) - T(1);\n        for (uint64_t value = 1; value <= _sqrt_n; value++) {\n\
    \            result[index(value)] = triangular(value) - T(1);\n        }\n\n \
    \       for (int prime_int : _primes) {\n            const uint64_t prime = static_cast<uint64_t>(prime_int);\n\
    \            const uint64_t square = prime * prime;\n            const T before\
    \ = result[index(prime - 1)];\n            const uint64_t end = std::min(_large_size,\
    \ _n / square + 1);\n            uint64_t product = prime;\n            for (uint64_t\
    \ i = 1; i < end; i++, product += prime) {\n                result[i] -= (result[index(_n\
    \ / product)] - before) * T(prime);\n            }\n            for (uint64_t\
    \ value = _sqrt_n; value >= square; value--) {\n                result[index(value)]\
    \ -= (result[index(value / prime)] - before) * T(prime);\n            }\n    \
    \    }\n        return result;\n    }\n\n    // Returns sum_{k=1}^x f(k) at every\
    \ represented x.\n    std::vector<T> prefix_sum_table(const std::vector<T>& prime_prefix)\
    \ const {\n        if (_n == 0) {\n            assert(prime_prefix.empty());\n\
    \            return {};\n        }\n        assert(static_cast<int>(prime_prefix.size())\
    \ == table_size());\n\n        const std::vector<uint64_t> values = quotient_values();\n\
    \        std::vector<T> result = prime_prefix;\n        std::vector<T> next =\
    \ prime_prefix;\n        for (int prime_index = static_cast<int>(_primes.size())\
    \ - 1; prime_index >= 0; prime_index--) {\n            const uint64_t prime =\
    \ static_cast<uint64_t>(_primes[prime_index]);\n            uint64_t power = prime;\n\
    \            int exponent = 1;\n            while (power <= _n / prime) {\n  \
    \              const T current_value = _prime_power(prime, exponent);\n      \
    \          const T next_value = _prime_power(prime, exponent + 1);\n         \
    \       const T primes_before = prime_prefix[index(prime)];\n                for\
    \ (int i = 1; i < table_size(); i++) {\n                    const uint64_t value\
    \ = values[i];\n                    if (value < power * prime) break;\n      \
    \              next[i] += current_value * (result[index(value / power)] - primes_before)\
    \ + next_value;\n                }\n                exponent++;\n            \
    \    power *= prime;\n            }\n            const uint64_t bound = prime\
    \ * prime;\n            const int copy_size = std::min(table_size(), index(bound)\
    \ + 1);\n            std::copy(next.begin(), next.begin() + copy_size, result.begin());\n\
    \        }\n        for (int i = 1; i < table_size(); i++) result[i] += T(1);\n\
    \        return result;\n    }\n\n    T prefix_sum(const std::vector<T>& prime_prefix)\
    \ const {\n        if (_n == 0) {\n            assert(prime_prefix.empty());\n\
    \            return T{};\n        }\n        return prefix_sum_table(prime_prefix)[index(_n)];\n\
    \    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_MULTIPLICATIVE_FUNCTION_PREFIX_SUM_HPP\n#define M1UNE_MATH_MULTIPLICATIVE_FUNCTION_PREFIX_SUM_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <cstdint>\n\
    #include <limits>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace math {\n\n// Computes summatory multiplicative functions with a Min_25\
    \ sieve.\n// prime_power(p, e) must return f(p^e), and prime_prefix must contain\n\
    // sum_{p <= x} f(p) at every x represented by quotient_values().\ntemplate <class\
    \ T, class PrimePower>\nstruct MultiplicativeFunctionPrefixSum {\n   private:\n\
    \    uint64_t _n;\n    uint64_t _sqrt_n;\n    uint64_t _large_size;\n    std::vector<int>\
    \ _primes;\n    PrimePower _prime_power;\n\n    static uint64_t integer_sqrt(uint64_t\
    \ n) {\n        uint64_t result = static_cast<uint64_t>(std::sqrt(static_cast<long\
    \ double>(n)));\n        while (result != 0 && result > n / result) result--;\n\
    \        while (result + 1 <= n / (result + 1)) result++;\n        return result;\n\
    \    }\n\n    static uint64_t validated_sqrt(uint64_t n) {\n        const uint64_t\
    \ result = integer_sqrt(n);\n        assert(result <= static_cast<uint64_t>(std::numeric_limits<int>::max()\
    \ / 2));\n        return result;\n    }\n\n    static std::vector<int> enumerate_primes(uint64_t\
    \ limit) {\n        assert(limit <= static_cast<uint64_t>(std::numeric_limits<int>::max()));\n\
    \        const int n = static_cast<int>(limit);\n        std::vector<bool> is_composite(n\
    \ + 1);\n        std::vector<int> primes;\n        for (int value = 2; value <=\
    \ n; value++) {\n            if (!is_composite[value]) primes.push_back(value);\n\
    \            for (int prime : primes) {\n                if (value > n / prime)\
    \ break;\n                is_composite[value * prime] = true;\n              \
    \  if (value % prime == 0) break;\n            }\n        }\n        return primes;\n\
    \    }\n\n    T triangular(uint64_t n) const {\n        if ((n & 1) == 0) return\
    \ T(n / 2) * T(n + 1);\n        return T(n) * T((n + 1) / 2);\n    }\n\n   public:\n\
    \    explicit MultiplicativeFunctionPrefixSum(uint64_t n, PrimePower prime_power)\n\
    \        : _n(n),\n          _sqrt_n(validated_sqrt(n)),\n          _large_size(n\
    \ == 0 ? 0 : n / _sqrt_n),\n          _primes(enumerate_primes(_sqrt_n)),\n  \
    \        _prime_power(std::move(prime_power)) {\n        if (n == 0) return;\n\
    \        while (_large_size > 1 && n / (_large_size - 1) == _sqrt_n) _large_size--;\n\
    \    }\n\n    uint64_t n() const {\n        return _n;\n    }\n\n    uint64_t\
    \ sqrt_n() const {\n        return _sqrt_n;\n    }\n\n    const std::vector<int>&\
    \ primes() const {\n        return _primes;\n    }\n\n    int table_size() const\
    \ {\n        if (_n == 0) return 0;\n        return static_cast<int>(_large_size\
    \ + _sqrt_n);\n    }\n\n    // Returns the table index representing x. The argument\
    \ must be one of the\n    // values returned by quotient_values().\n    int index(uint64_t\
    \ x) const {\n        assert(_n > 0 && 1 <= x && x <= _n);\n        if (x <= _sqrt_n)\
    \ return table_size() - static_cast<int>(x);\n        const uint64_t result =\
    \ _n / x;\n        assert(result < _large_size);\n        return static_cast<int>(result);\n\
    \    }\n\n    // table[i] represents the value at quotient_values()[i]. Index\
    \ zero is a\n    // dummy entry; the represented values occupy indices [1, table_size()).\n\
    \    std::vector<uint64_t> quotient_values() const {\n        if (_n == 0) return\
    \ {};\n        std::vector<uint64_t> result(table_size());\n        for (uint64_t\
    \ i = 1; i < _large_size; i++) result[i] = _n / i;\n        for (uint64_t value\
    \ = 1; value <= _sqrt_n; value++) {\n            result[index(value)] = value;\n\
    \        }\n        return result;\n    }\n\n    // Returns pi(x) at every represented\
    \ x.\n    std::vector<T> prime_count_table() const {\n        if (_n == 0) return\
    \ {};\n        std::vector<uint64_t> large(_large_size);\n        for (uint64_t\
    \ i = 1; i < _large_size; i++) large[i] = _n / i - 1;\n\n        std::vector<uint64_t>\
    \ small(_sqrt_n + 1);\n        for (uint64_t value = 1; value <= _sqrt_n; value++)\
    \ small[value] = value - 1;\n\n        uint64_t prime_count = 0;\n        for\
    \ (int prime_int : _primes) {\n            const uint64_t prime = static_cast<uint64_t>(prime_int);\n\
    \            const uint64_t square = prime * prime;\n            const uint64_t\
    \ end = std::min(_large_size, _n / square + 1);\n            uint64_t product\
    \ = prime;\n            for (uint64_t i = 1; i < end; i++, product += prime) {\n\
    \                const uint64_t previous = product < _large_size ? large[product]\
    \ : small[_n / product];\n                large[i] -= previous - prime_count;\n\
    \            }\n            for (uint64_t value = _sqrt_n; value >= square; value--)\
    \ {\n                small[value] -= small[value / prime] - prime_count;\n   \
    \         }\n            prime_count++;\n        }\n\n        std::vector<T> result(table_size());\n\
    \        for (uint64_t i = 0; i < _large_size; i++) result[i] = T(large[i]);\n\
    \        for (uint64_t value = 1; value <= _sqrt_n; value++) result[index(value)]\
    \ = T(small[value]);\n        return result;\n    }\n\n    // Returns sum_{p <=\
    \ x} p at every represented x.\n    std::vector<T> prime_sum_table() const {\n\
    \        if (_n == 0) return {};\n        std::vector<T> result(table_size());\n\
    \        for (uint64_t i = 1; i < _large_size; i++) result[i] = triangular(_n\
    \ / i) - T(1);\n        for (uint64_t value = 1; value <= _sqrt_n; value++) {\n\
    \            result[index(value)] = triangular(value) - T(1);\n        }\n\n \
    \       for (int prime_int : _primes) {\n            const uint64_t prime = static_cast<uint64_t>(prime_int);\n\
    \            const uint64_t square = prime * prime;\n            const T before\
    \ = result[index(prime - 1)];\n            const uint64_t end = std::min(_large_size,\
    \ _n / square + 1);\n            uint64_t product = prime;\n            for (uint64_t\
    \ i = 1; i < end; i++, product += prime) {\n                result[i] -= (result[index(_n\
    \ / product)] - before) * T(prime);\n            }\n            for (uint64_t\
    \ value = _sqrt_n; value >= square; value--) {\n                result[index(value)]\
    \ -= (result[index(value / prime)] - before) * T(prime);\n            }\n    \
    \    }\n        return result;\n    }\n\n    // Returns sum_{k=1}^x f(k) at every\
    \ represented x.\n    std::vector<T> prefix_sum_table(const std::vector<T>& prime_prefix)\
    \ const {\n        if (_n == 0) {\n            assert(prime_prefix.empty());\n\
    \            return {};\n        }\n        assert(static_cast<int>(prime_prefix.size())\
    \ == table_size());\n\n        const std::vector<uint64_t> values = quotient_values();\n\
    \        std::vector<T> result = prime_prefix;\n        std::vector<T> next =\
    \ prime_prefix;\n        for (int prime_index = static_cast<int>(_primes.size())\
    \ - 1; prime_index >= 0; prime_index--) {\n            const uint64_t prime =\
    \ static_cast<uint64_t>(_primes[prime_index]);\n            uint64_t power = prime;\n\
    \            int exponent = 1;\n            while (power <= _n / prime) {\n  \
    \              const T current_value = _prime_power(prime, exponent);\n      \
    \          const T next_value = _prime_power(prime, exponent + 1);\n         \
    \       const T primes_before = prime_prefix[index(prime)];\n                for\
    \ (int i = 1; i < table_size(); i++) {\n                    const uint64_t value\
    \ = values[i];\n                    if (value < power * prime) break;\n      \
    \              next[i] += current_value * (result[index(value / power)] - primes_before)\
    \ + next_value;\n                }\n                exponent++;\n            \
    \    power *= prime;\n            }\n            const uint64_t bound = prime\
    \ * prime;\n            const int copy_size = std::min(table_size(), index(bound)\
    \ + 1);\n            std::copy(next.begin(), next.begin() + copy_size, result.begin());\n\
    \        }\n        for (int i = 1; i < table_size(); i++) result[i] += T(1);\n\
    \        return result;\n    }\n\n    T prefix_sum(const std::vector<T>& prime_prefix)\
    \ const {\n        if (_n == 0) {\n            assert(prime_prefix.empty());\n\
    \            return T{};\n        }\n        return prefix_sum_table(prime_prefix)[index(_n)];\n\
    \    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_MULTIPLICATIVE_FUNCTION_PREFIX_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/multiplicative_function_prefix_sum.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-13 03:44:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/enumerate_quotients.test.cpp
  - verify/math/sum_of_multiplicative_function.test.cpp
  - verify/math/counting_primes.test.cpp
documentation_of: math/multiplicative_function_prefix_sum.hpp
layout: document
title: Multiplicative Function Prefix Sum
---

## Overview

`MultiplicativeFunctionPrefixSum` uses a Min_25 sieve to compute

$$
F(x) = \sum_{k=1}^{x} f(k)
$$

for a multiplicative function `f`. It computes `F(n)` and, when useful, all
`F(floor(n / i))` in one run without enumerating every integer through `n`.

The caller supplies two descriptions of the function:

* `prime_power(p, e)` returns `f(p^e)` for a prime `p` and positive `e`.
* `prime_prefix[index(x)]` equals the sum of `f(p)` over primes `p <= x`.

The second part depends on the problem. The header provides tables for prime
counts and prime sums, which cover common formulas such as `f(p) = a + b * p`.
More general functions may build the required prime-prefix table separately.

## Requirements

`f` must be multiplicative and satisfy `f(1) = 1`.

The value type `T` must be constructible from the used integer types and support
default construction, addition, subtraction, and multiplication. In typical
use, `T` is a modular integer type. `PrimePower` must be callable as
`T(uint64_t prime, int exponent)`.

The argument `n` and all intermediate prime powers must fit in `uint64_t`.
The table has about `2 * sqrt(n)` entries and its size must fit in `int`.

## API

```cpp
template <class T, class PrimePower>
struct MultiplicativeFunctionPrefixSum {
    explicit MultiplicativeFunctionPrefixSum(
        uint64_t n,
        PrimePower prime_power
    );

    uint64_t n() const;
    uint64_t sqrt_n() const;
    const std::vector<int>& primes() const;
    int table_size() const;
    int index(uint64_t x) const;

    std::vector<uint64_t> quotient_values() const;
    std::vector<T> prime_count_table() const;
    std::vector<T> prime_sum_table() const;
    std::vector<T> prefix_sum_table(
        const std::vector<T>& prime_prefix
    ) const;
    T prefix_sum(const std::vector<T>& prime_prefix) const;
};
```

### Table layout

`quotient_values()` contains every distinct value `floor(n / i)`, together
with a dummy element at index zero. For each represented positive `x`,
`index(x)` is its table position. Every table accepted or returned by the class
uses this same layout.

`prime_count_table()` stores `pi(x)`, the number of primes at most `x`.
`prime_sum_table()` stores the sum of primes at most `x`.

`prefix_sum_table(prime_prefix)` returns `F(x)` at all represented `x`.
`prefix_sum(prime_prefix)` returns only `F(n)`. Neither method mutates the
solver or its input table. When `n = 0`, tables are empty and `prefix_sum`
returns `T{}`.

## Complexity

Let `N = n`.

| Method | Time | Extra returned memory |
| --- | --- | --- |
| Constructor | $O(\sqrt N)$ | $O(\sqrt N)$ in the object |
| `n`, `sqrt_n`, `primes`, `table_size`, `index` | $O(1)$ | $O(1)$ |
| `quotient_values` | $O(\sqrt N)$ | $O(\sqrt N)$ |
| `prime_count_table`, `prime_sum_table` | $O(N^{3/4} / \log N)$ | $O(\sqrt N)$ |
| `prefix_sum_table`, `prefix_sum` | $O(N^{3/4} / \log N)$ calls and ring operations | $O(\sqrt N)$ |

The bounds for the sieve methods are the standard Min_25 bounds; small values
have the expected lower practical cost.

## Example

This computes the Library Checker function defined by
`f(p^e) = a * e + b * p`.

```cpp
#include "math/modint.hpp"
#include "math/multiplicative_function_prefix_sum.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

using Mint = m1une::math::ModInt<469762049>;

int main() {
    uint64_t n = 1000000;
    Mint a = 2;
    Mint b = 3;

    auto prime_power = [a, b](uint64_t p, int e) {
        return a * Mint(e) + b * Mint(p);
    };
    using Solver = m1une::math::MultiplicativeFunctionPrefixSum<
        Mint,
        decltype(prime_power)
    >;
    Solver solver(n, prime_power);

    std::vector<Mint> prime_prefix = solver.prime_count_table();
    std::vector<Mint> prime_sum = solver.prime_sum_table();
    for (int i = 0; i < solver.table_size(); i++) {
        prime_prefix[i] = a * prime_prefix[i] + b * prime_sum[i];
    }

    std::cout << solver.prefix_sum(prime_prefix) << '\n';
}
```
