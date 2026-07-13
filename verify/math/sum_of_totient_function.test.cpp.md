---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/totient_sum.hpp
    title: Totient Sum
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_totient_function
    links:
    - https://judge.yosupo.jp/problem/sum_of_totient_function
  bundledCode: "#line 1 \"verify/math/sum_of_totient_function.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/sum_of_totient_function\"\n\n#line\
    \ 1 \"math/totient_sum.hpp\"\n\n\n\n#include <cassert>\n#include <cstdint>\n#include\
    \ <unordered_map>\n#include <vector>\n\nnamespace m1une {\nnamespace math {\n\n\
    struct TotientSum {\n   private:\n    int _precalculation_limit;\n    std::vector<__uint128_t>\
    \ _prefix_sum;\n    std::unordered_map<uint64_t, __uint128_t> _memo;\n\n    __uint128_t\
    \ solve(uint64_t n) {\n        if (n <= static_cast<uint64_t>(_precalculation_limit))\
    \ {\n            return _prefix_sum[static_cast<int>(n)];\n        }\n       \
    \ if (auto it = _memo.find(n); it != _memo.end()) {\n            return it->second;\n\
    \        }\n\n        const __uint128_t wide_n = n;\n        __uint128_t result\
    \ = wide_n * (wide_n + 1) / 2;\n        for (uint64_t left = 2; left <= n;) {\n\
    \            const uint64_t quotient = n / left;\n            const uint64_t right\
    \ = n / quotient;\n            result -= static_cast<__uint128_t>(right - left\
    \ + 1) * solve(quotient);\n            if (right == n) break;\n            left\
    \ = right + 1;\n        }\n\n        _memo.emplace(n, result);\n        return\
    \ result;\n    }\n\n   public:\n    explicit TotientSum(int precalculation_limit\
    \ = 1000000) : _precalculation_limit(precalculation_limit) {\n        assert(precalculation_limit\
    \ >= 0);\n\n        std::vector<uint64_t> phi(precalculation_limit + 1);\n   \
    \     std::vector<int> primes;\n        std::vector<bool> is_composite(precalculation_limit\
    \ + 1);\n        if (precalculation_limit >= 1) {\n            phi[1] = 1;\n \
    \       }\n        for (int value = 2; value <= precalculation_limit; value++)\
    \ {\n            if (!is_composite[value]) {\n                primes.push_back(value);\n\
    \                phi[value] = static_cast<uint64_t>(value - 1);\n            }\n\
    \            for (int prime : primes) {\n                if (value > precalculation_limit\
    \ / prime) break;\n                const int next = value * prime;\n         \
    \       is_composite[next] = true;\n                if (value % prime == 0) {\n\
    \                    phi[next] = phi[value] * static_cast<uint64_t>(prime);\n\
    \                    break;\n                }\n                phi[next] = phi[value]\
    \ * static_cast<uint64_t>(prime - 1);\n            }\n        }\n\n        _prefix_sum.assign(precalculation_limit\
    \ + 1, 0);\n        for (int value = 1; value <= precalculation_limit; value++)\
    \ {\n            _prefix_sum[value] = _prefix_sum[value - 1] + phi[value];\n \
    \       }\n    }\n\n    int precalculation_limit() const {\n        return _precalculation_limit;\n\
    \    }\n\n    // Returns sum_{i=1}^n phi(i).\n    __uint128_t prefix_sum(uint64_t\
    \ n) {\n        return solve(n);\n    }\n\n    __uint128_t operator()(uint64_t\
    \ n) {\n        return prefix_sum(n);\n    }\n};\n\ninline __uint128_t totient_sum(uint64_t\
    \ n, int precalculation_limit = 1000000) {\n    TotientSum solver(precalculation_limit);\n\
    \    return solver.prefix_sum(n);\n}\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/math/sum_of_totient_function.test.cpp\"\n\n#line\
    \ 6 \"verify/math/sum_of_totient_function.test.cpp\"\n#include <iostream>\n\n\
    int main() {\n    std::uint64_t n;\n    std::cin >> n;\n    constexpr std::uint64_t\
    \ modulus = 998244353;\n    __uint128_t answer = m1une::math::totient_sum(n);\n\
    \    std::cout << static_cast<std::uint64_t>(answer % modulus) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_totient_function\"\
    \n\n#include \"../../math/totient_sum.hpp\"\n\n#include <cstdint>\n#include <iostream>\n\
    \nint main() {\n    std::uint64_t n;\n    std::cin >> n;\n    constexpr std::uint64_t\
    \ modulus = 998244353;\n    __uint128_t answer = m1une::math::totient_sum(n);\n\
    \    std::cout << static_cast<std::uint64_t>(answer % modulus) << '\\n';\n}\n"
  dependsOn:
  - math/totient_sum.hpp
  isVerificationFile: true
  path: verify/math/sum_of_totient_function.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 03:22:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/sum_of_totient_function.test.cpp
layout: document
redirect_from:
- /verify/verify/math/sum_of_totient_function.test.cpp
- /verify/verify/math/sum_of_totient_function.test.cpp.html
title: verify/math/sum_of_totient_function.test.cpp
---
