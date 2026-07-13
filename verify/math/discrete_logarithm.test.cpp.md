---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/discrete_logarithm.hpp
    title: Discrete Logarithm
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/discrete_logarithm_mod
    links:
    - https://judge.yosupo.jp/problem/discrete_logarithm_mod
  bundledCode: "#line 1 \"verify/math/discrete_logarithm.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/discrete_logarithm_mod\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <optional>\n#include <vector>\n\
    \n#line 1 \"math/discrete_logarithm.hpp\"\n\n\n\n#line 5 \"math/discrete_logarithm.hpp\"\
    \n#include <cmath>\n#include <cstddef>\n#line 8 \"math/discrete_logarithm.hpp\"\
    \n#include <numeric>\n#line 10 \"math/discrete_logarithm.hpp\"\n#include <unordered_map>\n\
    \nnamespace m1une {\nnamespace math {\n\nnamespace internal {\n\ninline uint64_t\
    \ discrete_logarithm_multiply(\n    uint64_t first,\n    uint64_t second,\n  \
    \  uint64_t mod\n) {\n    return static_cast<uint64_t>(static_cast<unsigned __int128>(first)\
    \ * second % mod);\n}\n\ninline uint64_t discrete_logarithm_power(\n    uint64_t\
    \ base,\n    uint64_t exponent,\n    uint64_t mod\n) {\n    uint64_t result =\
    \ 1 % mod;\n    base %= mod;\n    while (exponent > 0) {\n        if (exponent\
    \ & 1) result = discrete_logarithm_multiply(result, base, mod);\n        base\
    \ = discrete_logarithm_multiply(base, base, mod);\n        exponent >>= 1;\n \
    \   }\n    return result;\n}\n\ninline uint64_t discrete_logarithm_ceil_sqrt(uint64_t\
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
    }  // namespace m1une\n\n\n#line 10 \"verify/math/discrete_logarithm.test.cpp\"\
    \n\nnamespace {\n\n#ifndef NDEBUG\nstd::optional<uint64_t> brute_discrete_logarithm(\n\
    \    uint64_t base,\n    uint64_t target,\n    uint64_t mod\n) {\n    if (mod\
    \ == 1) return uint64_t(0);\n    base %= mod;\n    target %= mod;\n    uint64_t\
    \ value = 1 % mod;\n    std::vector<char> visited(mod, false);\n    for (uint64_t\
    \ exponent = 0; !visited[value]; exponent++) {\n        if (value == target) return\
    \ exponent;\n        visited[value] = true;\n        value = value * base % mod;\n\
    \    }\n    return std::nullopt;\n}\n\nvoid exhaustive_test() {\n    for (uint64_t\
    \ mod = 1; mod <= 180; mod++) {\n        for (uint64_t base = 0; base < mod; base++)\
    \ {\n            for (uint64_t target = 0; target < mod; target++) {\n       \
    \         auto expected = brute_discrete_logarithm(base, target, mod);\n     \
    \           auto actual = m1une::math::discrete_logarithm(base, target, mod);\n\
    \                assert(actual == expected);\n            }\n        }\n    }\n\
    \n    assert(m1une::math::discrete_logarithm(2, 8, 13) == uint64_t(3));\n    assert(m1une::math::discrete_logarithm(0,\
    \ 1, 17) == uint64_t(0));\n    assert(m1une::math::discrete_logarithm(0, 0, 17)\
    \ == uint64_t(1));\n    assert(m1une::math::discrete_logarithm(4, 2, 14) == uint64_t(2));\n\
    \    assert(!m1une::math::discrete_logarithm(4, 3, 14).has_value());\n    assert(m1une::math::discrete_logarithm(6,\
    \ 0, 72) == uint64_t(3));\n}\n#endif\n\n}  // namespace\n\nint main() {\n#ifndef\
    \ NDEBUG\n    exhaustive_test();\n#endif\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int query_count;\n    std::cin >> query_count;\n\
    \    while (query_count--) {\n        uint64_t base, target, mod;\n        std::cin\
    \ >> base >> target >> mod;\n        auto answer = m1une::math::discrete_logarithm(base,\
    \ target, mod);\n        if (answer.has_value()) {\n            std::cout << *answer\
    \ << '\\n';\n        } else {\n            std::cout << -1 << '\\n';\n       \
    \ }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/discrete_logarithm_mod\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <optional>\n\
    #include <vector>\n\n#include \"../../math/discrete_logarithm.hpp\"\n\nnamespace\
    \ {\n\n#ifndef NDEBUG\nstd::optional<uint64_t> brute_discrete_logarithm(\n   \
    \ uint64_t base,\n    uint64_t target,\n    uint64_t mod\n) {\n    if (mod ==\
    \ 1) return uint64_t(0);\n    base %= mod;\n    target %= mod;\n    uint64_t value\
    \ = 1 % mod;\n    std::vector<char> visited(mod, false);\n    for (uint64_t exponent\
    \ = 0; !visited[value]; exponent++) {\n        if (value == target) return exponent;\n\
    \        visited[value] = true;\n        value = value * base % mod;\n    }\n\
    \    return std::nullopt;\n}\n\nvoid exhaustive_test() {\n    for (uint64_t mod\
    \ = 1; mod <= 180; mod++) {\n        for (uint64_t base = 0; base < mod; base++)\
    \ {\n            for (uint64_t target = 0; target < mod; target++) {\n       \
    \         auto expected = brute_discrete_logarithm(base, target, mod);\n     \
    \           auto actual = m1une::math::discrete_logarithm(base, target, mod);\n\
    \                assert(actual == expected);\n            }\n        }\n    }\n\
    \n    assert(m1une::math::discrete_logarithm(2, 8, 13) == uint64_t(3));\n    assert(m1une::math::discrete_logarithm(0,\
    \ 1, 17) == uint64_t(0));\n    assert(m1une::math::discrete_logarithm(0, 0, 17)\
    \ == uint64_t(1));\n    assert(m1une::math::discrete_logarithm(4, 2, 14) == uint64_t(2));\n\
    \    assert(!m1une::math::discrete_logarithm(4, 3, 14).has_value());\n    assert(m1une::math::discrete_logarithm(6,\
    \ 0, 72) == uint64_t(3));\n}\n#endif\n\n}  // namespace\n\nint main() {\n#ifndef\
    \ NDEBUG\n    exhaustive_test();\n#endif\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int query_count;\n    std::cin >> query_count;\n\
    \    while (query_count--) {\n        uint64_t base, target, mod;\n        std::cin\
    \ >> base >> target >> mod;\n        auto answer = m1une::math::discrete_logarithm(base,\
    \ target, mod);\n        if (answer.has_value()) {\n            std::cout << *answer\
    \ << '\\n';\n        } else {\n            std::cout << -1 << '\\n';\n       \
    \ }\n    }\n}\n"
  dependsOn:
  - math/discrete_logarithm.hpp
  isVerificationFile: true
  path: verify/math/discrete_logarithm.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 19:59:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/discrete_logarithm.test.cpp
layout: document
redirect_from:
- /verify/verify/math/discrete_logarithm.test.cpp
- /verify/verify/math/discrete_logarithm.test.cpp.html
title: verify/math/discrete_logarithm.test.cpp
---
