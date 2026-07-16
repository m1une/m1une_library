---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/modular_kth_root.hpp
    title: Modular Kth Root
  - icon: ':heavy_check_mark:'
    path: math/squarefree_count.hpp
    title: Squarefree Count
  - icon: ':heavy_check_mark:'
    path: math/two_square_sum.hpp
    title: Sum of Two Squares
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/integer_arithmetic.test.cpp
    title: verify/math/integer_arithmetic.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/modular_kth_root.test.cpp
    title: verify/math/modular_kth_root.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/squarefree_count.test.cpp
    title: verify/math/squarefree_count.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/two_square_sum.test.cpp
    title: verify/math/two_square_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/two_square_sum.test.cpp
    title: verify/math/two_square_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/integer_arithmetic.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <limits>\n#include <optional>\n#include <type_traits>\n\
    \nnamespace m1une {\nnamespace math {\n\nnamespace integer_arithmetic_detail {\n\
    \ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\n\
    constexpr std::optional<T> checked_multiply(T first, T second) {\n    constexpr\
    \ T minimum = std::numeric_limits<T>::min();\n    constexpr T maximum = std::numeric_limits<T>::max();\n\
    \n    if constexpr (std::unsigned_integral<T>) {\n        if (second != 0 && maximum\
    \ / second < first) return std::nullopt;\n    } else {\n        if (0 < first)\
    \ {\n            if (0 < second) {\n                if (maximum / second < first)\
    \ return std::nullopt;\n            } else if (second < minimum / first) {\n \
    \               return std::nullopt;\n            }\n        } else if (first\
    \ < 0) {\n            if (0 < second) {\n                if (first < minimum /\
    \ second) return std::nullopt;\n            } else if (second < maximum / first)\
    \ {\n                return std::nullopt;\n            }\n        }\n    }\n \
    \   return T(first * second);\n}\n\ntemplate <std::unsigned_integral T>\nconstexpr\
    \ bool kth_power_leq(T base, unsigned exponent, T limit) {\n    assert(exponent\
    \ > 0);\n    if (base <= 1) return base <= limit;\n\n    const T multiplication_limit\
    \ = limit / base;\n    T product = 1;\n    for (unsigned i = 0; i < exponent;\
    \ i++) {\n        if (product > multiplication_limit) return false;\n        product\
    \ *= base;\n    }\n    return true;\n}\n\n}  // namespace integer_arithmetic_detail\n\
    \n// Returns floor(sqrt(value)) exactly, without floating-point arithmetic.\n\
    template <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\n\
    constexpr T isqrt(T value) {\n    if constexpr (std::signed_integral<T>) assert(0\
    \ <= value);\n    if (value <= 1) return value;\n\n    T low = 1;\n    T high\
    \ = value / 2 + 1;\n    while (low < high) {\n        T middle = low + (high -\
    \ low + 1) / 2;\n        if (middle <= value / middle) {\n            low = middle;\n\
    \        } else {\n            high = middle - 1;\n        }\n    }\n    return\
    \ low;\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
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
    \ exponent);\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_INTEGER_ARITHMETIC_HPP\n#define M1UNE_MATH_INTEGER_ARITHMETIC_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <limits>\n#include <optional>\n\
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
    \ exponent);\n}\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_INTEGER_ARITHMETIC_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/integer_arithmetic.hpp
  requiredBy:
  - math/all.hpp
  - math/squarefree_count.hpp
  - math/modular_kth_root.hpp
  - math/two_square_sum.hpp
  timestamp: '2026-07-15 01:09:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/integer_arithmetic.test.cpp
  - verify/math/modular_kth_root.test.cpp
  - verify/math/squarefree_count.test.cpp
  - verify/math/two_square_sum.test.cpp
  - verify/math/two_square_sum.test.cpp
documentation_of: math/integer_arithmetic.hpp
layout: document
title: Integer Roots and Powers
---

## Overview

This header provides exact integer roots and powers without converting through
floating point.

```cpp
isqrt(value);
ceil_sqrt(value);
floor_kth_root(value, degree);
ipow(base, exponent);
checked_ipow(base, exponent);
```

The descriptive aliases `floor_sqrt`, `integer_pow`, and
`checked_integer_pow` are also available.

All functions accept standard integral types except `bool`. Root inputs must be
non-negative. The degree passed to `floor_kth_root` must be positive, and power
exponents must be unsigned integers.

## Square Root

| Function | Result | Complexity |
| --- | --- | --- |
| `isqrt(value)` | $\lfloor\sqrt{\mathrm{value}}\rfloor$ | $O(\log \mathrm{value})$ |
| `floor_sqrt(value)` | Alias of `isqrt` | $O(\log \mathrm{value})$ |
| `ceil_sqrt(value)` | $\lceil\sqrt{\mathrm{value}}\rceil$ | $O(\log \mathrm{value})$ |

The implementation compares with division rather than multiplying candidate
roots, so it remains correct near the maximum value of the integer type.

## K-th Root

| Function | Exact signature | Result | Complexity |
| --- | --- | --- | --- |
| `floor_kth_root` | `template <std::integral T, std::integral Degree> constexpr T floor_kth_root(T value, Degree degree)` | $\lfloor\mathrm{value}^{1/\mathrm{degree}}\rfloor$ | $O(\log \mathrm{value})$ integer operations |

`value` must be non-negative and `degree` must be positive. Both signed and
unsigned degree types are accepted. In particular, degree `1` returns `value`.
For positive `value`, any degree at least the number of value bits returns `1`.

Candidate powers are compared to `value` using a division bound. No
intermediate multiplication can overflow, including for
`std::numeric_limits<std::uint64_t>::max()`.

## Integer Power

| Function | Result | Complexity |
| --- | --- | --- |
| `ipow(base, exponent)` | Exact `base` raised to `exponent` | $O(\log \mathrm{exponent})$ |
| `integer_pow(base, exponent)` | Alias of `ipow` | $O(\log \mathrm{exponent})$ |
| `checked_ipow(base, exponent)` | The power, or `std::nullopt` on overflow | $O(\log \mathrm{exponent})$ |
| `checked_integer_pow(base, exponent)` | Alias of `checked_ipow` | $O(\log \mathrm{exponent})$ |

`ipow` requires the result to fit in the base type and asserts this condition
in debug builds. Use `checked_ipow` when overflow is possible.

As usual, every nonzero integer to exponent zero is one. This library also
defines zero to exponent zero as one, which is convenient for binary
exponentiation and combinatorial formulas.

## Example

```cpp
#include "math/integer_arithmetic.hpp"

#include <iostream>

int main() {
    std::cout << m1une::math::isqrt(20LL) << "\n";      // 4
    std::cout << m1une::math::ceil_sqrt(20LL) << "\n"; // 5
    std::cout << m1une::math::floor_kth_root(1000ULL, 3) << "\n"; // 10
    std::cout << m1une::math::ipow(3LL, 10U) << "\n";  // 59049

    auto large = m1une::math::checked_ipow(10LL, 19U);
    if (!large) std::cout << "overflow\n";
}
```
