---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/integer_arithmetic.hpp
    title: Integer Roots and Powers
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/squarefree_count.test.cpp
    title: verify/math/squarefree_count.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/squarefree_count.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <limits>\n#include <vector>\n\
    \n#line 1 \"math/integer_arithmetic.hpp\"\n\n\n\n#line 5 \"math/integer_arithmetic.hpp\"\
    \n#include <concepts>\n#line 7 \"math/integer_arithmetic.hpp\"\n#include <optional>\n\
    #include <type_traits>\n\nnamespace m1une {\nnamespace math {\n\nnamespace integer_arithmetic_detail\
    \ {\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr std::optional<T> checked_multiply(T first, T second) {\n \
    \   constexpr T minimum = std::numeric_limits<T>::min();\n    constexpr T maximum\
    \ = std::numeric_limits<T>::max();\n\n    if constexpr (std::unsigned_integral<T>)\
    \ {\n        if (second != 0 && maximum / second < first) return std::nullopt;\n\
    \    } else {\n        if (0 < first) {\n            if (0 < second) {\n     \
    \           if (maximum / second < first) return std::nullopt;\n            }\
    \ else if (second < minimum / first) {\n                return std::nullopt;\n\
    \            }\n        } else if (first < 0) {\n            if (0 < second) {\n\
    \                if (first < minimum / second) return std::nullopt;\n        \
    \    } else if (second < maximum / first) {\n                return std::nullopt;\n\
    \            }\n        }\n    }\n    return T(first * second);\n}\n\ntemplate\
    \ <std::unsigned_integral T>\nconstexpr bool kth_power_leq(T base, unsigned exponent,\
    \ T limit) {\n    assert(exponent > 0);\n    if (base <= 1) return base <= limit;\n\
    \n    const T multiplication_limit = limit / base;\n    T product = 1;\n    for\
    \ (unsigned i = 0; i < exponent; i++) {\n        if (product > multiplication_limit)\
    \ return false;\n        product *= base;\n    }\n    return true;\n}\n\n}  //\
    \ namespace integer_arithmetic_detail\n\n// Returns floor(sqrt(value)) exactly,\
    \ without floating-point arithmetic.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr T isqrt(T value) {\n    if constexpr (std::signed_integral<T>)\
    \ assert(0 <= value);\n    if (value <= 1) return value;\n\n    T low = 1;\n \
    \   T high = value / 2 + 1;\n    while (low < high) {\n        T middle = low\
    \ + (high - low + 1) / 2;\n        if (middle <= value / middle) {\n         \
    \   low = middle;\n        } else {\n            high = middle - 1;\n        }\n\
    \    }\n    return low;\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr T floor_sqrt(T value) {\n    return isqrt(value);\n}\n\n//\
    \ Returns ceil(sqrt(value)) exactly, without floating-point arithmetic.\ntemplate\
    \ <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nconstexpr\
    \ T ceil_sqrt(T value) {\n    T result = isqrt(value);\n    if (result == 0) return\
    \ 0;\n    if (result != 0 && value / result == result && value % result == 0)\
    \ {\n        return result;\n    }\n    return result + 1;\n}\n\n// Returns floor(value^(1\
    \ / degree)) exactly, without floating-point arithmetic.\ntemplate <std::integral\
    \ T, std::integral Degree>\nrequires(\n    !std::same_as<std::remove_cv_t<T>,\
    \ bool>\n    && !std::same_as<std::remove_cv_t<Degree>, bool>\n)\nconstexpr T\
    \ floor_kth_root(T value, Degree degree) {\n    if constexpr (std::signed_integral<T>)\
    \ {\n        assert(0 <= value);\n        if (value < 0) return T();\n    }\n\
    \    assert(0 < degree);\n    if (degree <= 0) return T();\n    if (value <= 1\
    \ || degree == 1) return value;\n    if (degree == 2) return isqrt(value);\n\n\
    \    using U = std::make_unsigned_t<T>;\n    using UDegree = std::make_unsigned_t<Degree>;\n\
    \    constexpr int digits = std::numeric_limits<U>::digits;\n    const UDegree\
    \ unsigned_degree = static_cast<UDegree>(degree);\n    if (unsigned_degree >=\
    \ static_cast<UDegree>(digits)) return T(1);\n    const unsigned exponent = static_cast<unsigned>(unsigned_degree);\n\
    \    const U unsigned_value = static_cast<U>(value);\n\n    int bit_width = 0;\n\
    \    for (U remaining = unsigned_value; remaining != 0; remaining >>= 1) {\n \
    \       bit_width++;\n    }\n    const int root_bits =\n        (bit_width + static_cast<int>(exponent)\
    \ - 1) /\n        static_cast<int>(exponent);\n\n    U low = 1;\n    U high =\
    \ U(1) << root_bits;\n    while (high - low > 1) {\n        const U middle = low\
    \ + (high - low) / 2;\n        if (\n            integer_arithmetic_detail::kth_power_leq(\n\
    \                middle, exponent, unsigned_value\n            )\n        ) {\n\
    \            low = middle;\n        } else {\n            high = middle;\n   \
    \     }\n    }\n    return static_cast<T>(low);\n}\n\n// Returns base^exponent,\
    \ or nullopt when the result does not fit in T.\ntemplate <std::integral T, std::unsigned_integral\
    \ Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr std::optional<T> checked_ipow(T base, Exponent exponent)\
    \ {\n    T result = 1;\n    while (exponent != 0) {\n        if (exponent & 1)\
    \ {\n            auto product =\n                integer_arithmetic_detail::checked_multiply(result,\
    \ base);\n            if (!product.has_value()) return std::nullopt;\n       \
    \     result = *product;\n        }\n        exponent >>= 1;\n        if (exponent\
    \ != 0) {\n            auto square =\n                integer_arithmetic_detail::checked_multiply(base,\
    \ base);\n            if (!square.has_value()) return std::nullopt;\n        \
    \    base = *square;\n        }\n    }\n    return result;\n}\n\ntemplate <std::integral\
    \ T, std::unsigned_integral Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>,\
    \ bool>\n    && !std::same_as<std::remove_cv_t<Exponent>, bool>\n)\nconstexpr\
    \ std::optional<T> checked_integer_pow(T base, Exponent exponent) {\n    return\
    \ checked_ipow(base, exponent);\n}\n\n// Returns base^exponent. The result must\
    \ be representable by T.\ntemplate <std::integral T, std::unsigned_integral Exponent>\n\
    requires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr T ipow(T base, Exponent exponent) {\n    std::optional<T>\
    \ result = checked_ipow(base, exponent);\n    assert(result.has_value());\n  \
    \  return result.value_or(T());\n}\n\ntemplate <std::integral T, std::unsigned_integral\
    \ Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr T integer_pow(T base, Exponent exponent) {\n    return ipow(base,\
    \ exponent);\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 11 \"\
    math/squarefree_count.hpp\"\n\nnamespace m1une {\nnamespace math {\n\nnamespace\
    \ squarefree_count_detail {\n\ninline std::vector<int> mobius_prefix(int limit)\
    \ {\n    std::vector<std::int8_t> mobius(limit + 1, 0);\n    if (limit >= 1) mobius[1]\
    \ = 1;\n    {\n        std::vector<int> primes;\n        std::vector<bool> composite(limit\
    \ + 1, false);\n        for (int value = 2; value <= limit; value++) {\n     \
    \       if (!composite[value]) {\n                primes.push_back(value);\n \
    \               mobius[value] = -1;\n            }\n            for (int prime\
    \ : primes) {\n                if (prime > limit / value) break;\n           \
    \     const int product = prime * value;\n                composite[product] =\
    \ true;\n                if (value % prime == 0) {\n                    mobius[product]\
    \ = 0;\n                    break;\n                }\n                mobius[product]\
    \ = static_cast<std::int8_t>(-mobius[value]);\n            }\n        }\n    }\n\
    \n    std::vector<int> prefix(limit + 1, 0);\n    for (int value = 1; value <=\
    \ limit; value++) {\n        prefix[value] = prefix[value - 1] + mobius[value];\n\
    \    }\n    return prefix;\n}\n\n}  // namespace squarefree_count_detail\n\n//\
    \ Returns the number of square-free positive integers not greater than n.\ninline\
    \ uint64_t count_squarefree(uint64_t n) {\n    if (n == 0) return 0;\n\n    const\
    \ uint64_t split = std::max<uint64_t>(1, floor_kth_root(n, 5U));\n    const uint64_t\
    \ sieve_limit_u64 = isqrt(n / split);\n    assert(\n        sieve_limit_u64 <=\n\
    \        static_cast<uint64_t>(std::numeric_limits<int>::max())\n    );\n    const\
    \ int sieve_limit = static_cast<int>(sieve_limit_u64);\n    const std::vector<int>\
    \ mertens =\n        squarefree_count_detail::mobius_prefix(sieve_limit);\n\n\
    \    __int128_t direct_sum = 0;\n    for (int divisor = 1; divisor <= sieve_limit;\
    \ divisor++) {\n        direct_sum += static_cast<__int128_t>(\n            n\
    \ / static_cast<uint64_t>(divisor) /\n            static_cast<uint64_t>(divisor)\n\
    \        ) * (mertens[divisor] - mertens[divisor - 1]);\n    }\n\n    std::vector<std::int64_t>\
    \ large_mertens;\n    large_mertens.reserve(split - 1);\n    std::int64_t large_mertens_sum\
    \ = 0;\n    for (uint64_t index = split; index-- > 1;) {\n        const uint64_t\
    \ argument = isqrt(n / index);\n        const uint64_t square_root = isqrt(argument);\n\
    \        std::int64_t value = 1;\n\n        const uint64_t small_quotient_limit\
    \ =\n            argument / (square_root + 1);\n        for (uint64_t quotient\
    \ = 1;\n             quotient <= small_quotient_limit;\n             quotient++)\
    \ {\n            const uint64_t multiplicity =\n                argument / quotient\
    \ - argument / (quotient + 1);\n            value -= static_cast<std::int64_t>(multiplicity)\
    \ *\n                     mertens[static_cast<int>(quotient)];\n        }\n  \
    \      for (uint64_t divisor = 2; divisor <= square_root; divisor++) {\n     \
    \       const uint64_t quotient = argument / divisor;\n            if (quotient\
    \ <= sieve_limit_u64) {\n                value -= mertens[static_cast<int>(quotient)];\n\
    \            } else {\n                const uint64_t previous_argument =\n  \
    \                  index * divisor * divisor;\n                assert(previous_argument\
    \ < split);\n                const uint64_t position = split - previous_argument\
    \ - 1;\n                assert(position < large_mertens.size());\n           \
    \     value -= large_mertens[position];\n            }\n        }\n        large_mertens.push_back(value);\n\
    \        large_mertens_sum += value;\n    }\n\n    const std::int64_t grouped_sum\
    \ =\n        large_mertens_sum -\n        static_cast<std::int64_t>(split - 1)\
    \ * mertens[sieve_limit];\n    const __int128_t answer = direct_sum + grouped_sum;\n\
    \    assert(answer >= 0);\n    assert(answer <= std::numeric_limits<uint64_t>::max());\n\
    \    return static_cast<uint64_t>(answer);\n}\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_SQUAREFREE_COUNT_HPP\n#define M1UNE_MATH_SQUAREFREE_COUNT_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <limits>\n#include <vector>\n\n#include \"integer_arithmetic.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\nnamespace squarefree_count_detail {\n\ninline std::vector<int>\
    \ mobius_prefix(int limit) {\n    std::vector<std::int8_t> mobius(limit + 1, 0);\n\
    \    if (limit >= 1) mobius[1] = 1;\n    {\n        std::vector<int> primes;\n\
    \        std::vector<bool> composite(limit + 1, false);\n        for (int value\
    \ = 2; value <= limit; value++) {\n            if (!composite[value]) {\n    \
    \            primes.push_back(value);\n                mobius[value] = -1;\n \
    \           }\n            for (int prime : primes) {\n                if (prime\
    \ > limit / value) break;\n                const int product = prime * value;\n\
    \                composite[product] = true;\n                if (value % prime\
    \ == 0) {\n                    mobius[product] = 0;\n                    break;\n\
    \                }\n                mobius[product] = static_cast<std::int8_t>(-mobius[value]);\n\
    \            }\n        }\n    }\n\n    std::vector<int> prefix(limit + 1, 0);\n\
    \    for (int value = 1; value <= limit; value++) {\n        prefix[value] = prefix[value\
    \ - 1] + mobius[value];\n    }\n    return prefix;\n}\n\n}  // namespace squarefree_count_detail\n\
    \n// Returns the number of square-free positive integers not greater than n.\n\
    inline uint64_t count_squarefree(uint64_t n) {\n    if (n == 0) return 0;\n\n\
    \    const uint64_t split = std::max<uint64_t>(1, floor_kth_root(n, 5U));\n  \
    \  const uint64_t sieve_limit_u64 = isqrt(n / split);\n    assert(\n        sieve_limit_u64\
    \ <=\n        static_cast<uint64_t>(std::numeric_limits<int>::max())\n    );\n\
    \    const int sieve_limit = static_cast<int>(sieve_limit_u64);\n    const std::vector<int>\
    \ mertens =\n        squarefree_count_detail::mobius_prefix(sieve_limit);\n\n\
    \    __int128_t direct_sum = 0;\n    for (int divisor = 1; divisor <= sieve_limit;\
    \ divisor++) {\n        direct_sum += static_cast<__int128_t>(\n            n\
    \ / static_cast<uint64_t>(divisor) /\n            static_cast<uint64_t>(divisor)\n\
    \        ) * (mertens[divisor] - mertens[divisor - 1]);\n    }\n\n    std::vector<std::int64_t>\
    \ large_mertens;\n    large_mertens.reserve(split - 1);\n    std::int64_t large_mertens_sum\
    \ = 0;\n    for (uint64_t index = split; index-- > 1;) {\n        const uint64_t\
    \ argument = isqrt(n / index);\n        const uint64_t square_root = isqrt(argument);\n\
    \        std::int64_t value = 1;\n\n        const uint64_t small_quotient_limit\
    \ =\n            argument / (square_root + 1);\n        for (uint64_t quotient\
    \ = 1;\n             quotient <= small_quotient_limit;\n             quotient++)\
    \ {\n            const uint64_t multiplicity =\n                argument / quotient\
    \ - argument / (quotient + 1);\n            value -= static_cast<std::int64_t>(multiplicity)\
    \ *\n                     mertens[static_cast<int>(quotient)];\n        }\n  \
    \      for (uint64_t divisor = 2; divisor <= square_root; divisor++) {\n     \
    \       const uint64_t quotient = argument / divisor;\n            if (quotient\
    \ <= sieve_limit_u64) {\n                value -= mertens[static_cast<int>(quotient)];\n\
    \            } else {\n                const uint64_t previous_argument =\n  \
    \                  index * divisor * divisor;\n                assert(previous_argument\
    \ < split);\n                const uint64_t position = split - previous_argument\
    \ - 1;\n                assert(position < large_mertens.size());\n           \
    \     value -= large_mertens[position];\n            }\n        }\n        large_mertens.push_back(value);\n\
    \        large_mertens_sum += value;\n    }\n\n    const std::int64_t grouped_sum\
    \ =\n        large_mertens_sum -\n        static_cast<std::int64_t>(split - 1)\
    \ * mertens[sieve_limit];\n    const __int128_t answer = direct_sum + grouped_sum;\n\
    \    assert(answer >= 0);\n    assert(answer <= std::numeric_limits<uint64_t>::max());\n\
    \    return static_cast<uint64_t>(answer);\n}\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MATH_SQUAREFREE_COUNT_HPP\n"
  dependsOn:
  - math/integer_arithmetic.hpp
  isVerificationFile: false
  path: math/squarefree_count.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-16 21:30:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/squarefree_count.test.cpp
documentation_of: math/squarefree_count.hpp
layout: document
title: Squarefree Count
---

## Overview

`count_squarefree(n)` returns the number of square-free positive integers not
greater than `n`. An integer is square-free when it is not divisible by the
square of any prime.

The starting identity is

$$
Q(n)=\sum_{d\leq\sqrt n}\mu(d)
     \left\lfloor\frac{n}{d^2}\right\rfloor.
$$

Evaluating every term would require $O(\sqrt n)$ time. The implementation
chooses a fifth-root split, sieves the Möbius function through
$O(n^{2/5})$, and obtains the remaining grouped terms from selected values of
the Mertens prefix sum.

## Interface

```cpp
uint64_t count_squarefree(uint64_t n);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `count_squarefree(n)` | Counts square-free integers in `[1, n]`. Returns `0` for `n == 0`. | $O(n^{2/5})$ time and memory |

All roots are computed with exact integer arithmetic. The implementation
supports the full `uint64_t` input range for which its internal sieve limit fits
in `int`; in particular, it directly supports the Library Checker bound
$n\leq10^{18}$. The returned count never exceeds `n`.

## Example

```cpp
#include "math/squarefree_count.hpp"

#include <cassert>

int main() {
    assert(m1une::math::count_squarefree(10) == 7);
    assert(m1une::math::count_squarefree(100) == 61);
}
```
