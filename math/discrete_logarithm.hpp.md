---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/discrete_logarithm.test.cpp
    title: verify/math/discrete_logarithm.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/discrete_logarithm.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cmath>\n#include <cstddef>\n#include <cstdint>\n#include <numeric>\n\
    #include <optional>\n#include <unordered_map>\n\nnamespace m1une {\nnamespace\
    \ math {\n\nnamespace internal {\n\ninline uint64_t discrete_logarithm_multiply(\n\
    \    uint64_t first,\n    uint64_t second,\n    uint64_t mod\n) {\n    return\
    \ static_cast<uint64_t>(static_cast<unsigned __int128>(first) * second % mod);\n\
    }\n\ninline uint64_t discrete_logarithm_power(\n    uint64_t base,\n    uint64_t\
    \ exponent,\n    uint64_t mod\n) {\n    uint64_t result = 1 % mod;\n    base %=\
    \ mod;\n    while (exponent > 0) {\n        if (exponent & 1) result = discrete_logarithm_multiply(result,\
    \ base, mod);\n        base = discrete_logarithm_multiply(base, base, mod);\n\
    \        exponent >>= 1;\n    }\n    return result;\n}\n\ninline uint64_t discrete_logarithm_ceil_sqrt(uint64_t\
    \ value) {\n    uint64_t result = static_cast<uint64_t>(std::sqrt(static_cast<long\
    \ double>(value)));\n    while (static_cast<unsigned __int128>(result) * result\
    \ < value) result++;\n    while (result > 0 &&\n           static_cast<unsigned\
    \ __int128>(result - 1) * (result - 1) >= value) {\n        result--;\n    }\n\
    \    return result;\n}\n\nstruct DiscreteLogarithmHash {\n    std::size_t operator()(uint64_t\
    \ value) const {\n        value += 0x9e3779b97f4a7c15ULL;\n        value = (value\
    \ ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;\n        value = (value ^ (value >>\
    \ 27)) * 0x94d049bb133111ebULL;\n        value ^= value >> 31;\n        return\
    \ static_cast<std::size_t>(value);\n    }\n};\n\n// Solves coefficient * base^exponent\
    \ = target (mod mod) for a positive\n// exponent. Both coefficient and base must\
    \ be invertible modulo mod.\ninline std::optional<uint64_t> discrete_logarithm_coprime(\n\
    \    uint64_t coefficient,\n    uint64_t base,\n    uint64_t target,\n    uint64_t\
    \ mod\n) {\n    const uint64_t step = discrete_logarithm_ceil_sqrt(mod);\n   \
    \ std::unordered_map<uint64_t, uint64_t, DiscreteLogarithmHash> baby;\n    baby.max_load_factor(0.7F);\n\
    \    baby.reserve(static_cast<std::size_t>(step));\n\n    uint64_t value = target;\n\
    \    for (uint64_t exponent = 0; exponent < step; exponent++) {\n        baby[value]\
    \ = exponent;\n        value = discrete_logarithm_multiply(value, base, mod);\n\
    \    }\n\n    const uint64_t giant_factor = discrete_logarithm_power(base, step,\
    \ mod);\n    uint64_t giant = coefficient;\n    for (uint64_t block = 1; block\
    \ <= step; block++) {\n        giant = discrete_logarithm_multiply(giant, giant_factor,\
    \ mod);\n        auto it = baby.find(giant);\n        if (it == baby.end()) continue;\n\
    \        const unsigned __int128 candidate =\n            static_cast<unsigned\
    \ __int128>(block) * step - it->second;\n        if (candidate <= UINT64_MAX)\
    \ return static_cast<uint64_t>(candidate);\n    }\n    return std::nullopt;\n\
    }\n\n}  // namespace internal\n\n// Returns the smallest nonnegative exponent\
    \ x satisfying base^x = target\n// modulo mod, or nullopt when no such exponent\
    \ exists. Defines 0^0 as 1.\ninline std::optional<uint64_t> discrete_logarithm(\n\
    \    uint64_t base,\n    uint64_t target,\n    uint64_t mod\n) {\n    assert(mod\
    \ >= 1);\n    if (mod == 1) return uint64_t(0);\n    base %= mod;\n    target\
    \ %= mod;\n\n    uint64_t coefficient = 1;\n    uint64_t offset = 0;\n    while\
    \ (true) {\n        if (coefficient == target) return offset;\n        const uint64_t\
    \ divisor = std::gcd(base, mod);\n        if (divisor == 1) break;\n        if\
    \ (target % divisor != 0) return std::nullopt;\n        target /= divisor;\n \
    \       mod /= divisor;\n        coefficient = internal::discrete_logarithm_multiply(\n\
    \            coefficient % mod, (base / divisor) % mod, mod);\n        offset++;\n\
    \    }\n\n    auto remaining = internal::discrete_logarithm_coprime(\n       \
    \ coefficient, base % mod, target, mod);\n    if (!remaining.has_value()) return\
    \ std::nullopt;\n    return offset + *remaining;\n}\n\n}  // namespace math\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_DISCRETE_LOGARITHM_HPP\n#define M1UNE_MATH_DISCRETE_LOGARITHM_HPP\
    \ 1\n\n#include <cassert>\n#include <cmath>\n#include <cstddef>\n#include <cstdint>\n\
    #include <numeric>\n#include <optional>\n#include <unordered_map>\n\nnamespace\
    \ m1une {\nnamespace math {\n\nnamespace internal {\n\ninline uint64_t discrete_logarithm_multiply(\n\
    \    uint64_t first,\n    uint64_t second,\n    uint64_t mod\n) {\n    return\
    \ static_cast<uint64_t>(static_cast<unsigned __int128>(first) * second % mod);\n\
    }\n\ninline uint64_t discrete_logarithm_power(\n    uint64_t base,\n    uint64_t\
    \ exponent,\n    uint64_t mod\n) {\n    uint64_t result = 1 % mod;\n    base %=\
    \ mod;\n    while (exponent > 0) {\n        if (exponent & 1) result = discrete_logarithm_multiply(result,\
    \ base, mod);\n        base = discrete_logarithm_multiply(base, base, mod);\n\
    \        exponent >>= 1;\n    }\n    return result;\n}\n\ninline uint64_t discrete_logarithm_ceil_sqrt(uint64_t\
    \ value) {\n    uint64_t result = static_cast<uint64_t>(std::sqrt(static_cast<long\
    \ double>(value)));\n    while (static_cast<unsigned __int128>(result) * result\
    \ < value) result++;\n    while (result > 0 &&\n           static_cast<unsigned\
    \ __int128>(result - 1) * (result - 1) >= value) {\n        result--;\n    }\n\
    \    return result;\n}\n\nstruct DiscreteLogarithmHash {\n    std::size_t operator()(uint64_t\
    \ value) const {\n        value += 0x9e3779b97f4a7c15ULL;\n        value = (value\
    \ ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;\n        value = (value ^ (value >>\
    \ 27)) * 0x94d049bb133111ebULL;\n        value ^= value >> 31;\n        return\
    \ static_cast<std::size_t>(value);\n    }\n};\n\n// Solves coefficient * base^exponent\
    \ = target (mod mod) for a positive\n// exponent. Both coefficient and base must\
    \ be invertible modulo mod.\ninline std::optional<uint64_t> discrete_logarithm_coprime(\n\
    \    uint64_t coefficient,\n    uint64_t base,\n    uint64_t target,\n    uint64_t\
    \ mod\n) {\n    const uint64_t step = discrete_logarithm_ceil_sqrt(mod);\n   \
    \ std::unordered_map<uint64_t, uint64_t, DiscreteLogarithmHash> baby;\n    baby.max_load_factor(0.7F);\n\
    \    baby.reserve(static_cast<std::size_t>(step));\n\n    uint64_t value = target;\n\
    \    for (uint64_t exponent = 0; exponent < step; exponent++) {\n        baby[value]\
    \ = exponent;\n        value = discrete_logarithm_multiply(value, base, mod);\n\
    \    }\n\n    const uint64_t giant_factor = discrete_logarithm_power(base, step,\
    \ mod);\n    uint64_t giant = coefficient;\n    for (uint64_t block = 1; block\
    \ <= step; block++) {\n        giant = discrete_logarithm_multiply(giant, giant_factor,\
    \ mod);\n        auto it = baby.find(giant);\n        if (it == baby.end()) continue;\n\
    \        const unsigned __int128 candidate =\n            static_cast<unsigned\
    \ __int128>(block) * step - it->second;\n        if (candidate <= UINT64_MAX)\
    \ return static_cast<uint64_t>(candidate);\n    }\n    return std::nullopt;\n\
    }\n\n}  // namespace internal\n\n// Returns the smallest nonnegative exponent\
    \ x satisfying base^x = target\n// modulo mod, or nullopt when no such exponent\
    \ exists. Defines 0^0 as 1.\ninline std::optional<uint64_t> discrete_logarithm(\n\
    \    uint64_t base,\n    uint64_t target,\n    uint64_t mod\n) {\n    assert(mod\
    \ >= 1);\n    if (mod == 1) return uint64_t(0);\n    base %= mod;\n    target\
    \ %= mod;\n\n    uint64_t coefficient = 1;\n    uint64_t offset = 0;\n    while\
    \ (true) {\n        if (coefficient == target) return offset;\n        const uint64_t\
    \ divisor = std::gcd(base, mod);\n        if (divisor == 1) break;\n        if\
    \ (target % divisor != 0) return std::nullopt;\n        target /= divisor;\n \
    \       mod /= divisor;\n        coefficient = internal::discrete_logarithm_multiply(\n\
    \            coefficient % mod, (base / divisor) % mod, mod);\n        offset++;\n\
    \    }\n\n    auto remaining = internal::discrete_logarithm_coprime(\n       \
    \ coefficient, base % mod, target, mod);\n    if (!remaining.has_value()) return\
    \ std::nullopt;\n    return offset + *remaining;\n}\n\n}  // namespace math\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MATH_DISCRETE_LOGARITHM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/discrete_logarithm.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-11 19:59:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/discrete_logarithm.test.cpp
documentation_of: math/discrete_logarithm.hpp
layout: document
title: Discrete Logarithm
---

## Overview

`discrete_logarithm(base, target, mod)` finds the smallest nonnegative integer
`exponent` satisfying

$$
\text{base}^{\text{exponent}} \equiv \text{target} \pmod {\text{mod}}.
$$

The modulus may be prime or composite, and the base does not need to be
invertible. Common factors are removed first, followed by a baby-step--giant-step
search in the remaining multiplicative group.

## API

```cpp
std::optional<uint64_t> discrete_logarithm(
    uint64_t base,
    uint64_t target,
    uint64_t mod
);
```

| Function | Description | Expected complexity |
| --- | --- | --- |
| `discrete_logarithm(base, target, mod)` | Returns the smallest nonnegative solution, or `std::nullopt` when none exists. | $O(\sqrt m)$ time and memory |

The common-factor reduction takes $O(\log m)$ iterations. The hash-table search
uses $O(\sqrt m)$ modular multiplications and stored residues. Multiplication
uses an unsigned 128-bit intermediate.

`mod` must be positive. Both residues are reduced modulo `mod`. Exponent zero is
checked first, and `0^0` is defined as `1`; therefore a target congruent to `1`
always returns `0`. For `mod == 1`, the result is also `0`.

The function accepts 64-bit inputs, but its square-root memory requirement makes
very large moduli impractical in the usual way for baby-step--giant-step.

## Example

```cpp
#include "math/discrete_logarithm.hpp"

#include <iostream>

int main() {
    auto first = m1une::math::discrete_logarithm(2, 8, 13);
    std::cout << *first << "\n";  // 3

    auto second = m1une::math::discrete_logarithm(4, 3, 14);
    std::cout << second.has_value() << "\n";  // 0

    auto zero = m1une::math::discrete_logarithm(0, 0, 17);
    std::cout << *zero << "\n";  // 1
}
```
