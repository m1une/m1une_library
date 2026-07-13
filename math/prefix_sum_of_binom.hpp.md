---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/combinatorics.hpp
    title: Combinatorics
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':x:'
    path: verify/math/prefix_sum_of_binom.test.cpp
    title: verify/math/prefix_sum_of_binom.test.cpp
  - icon: ':x:'
    path: verify/math/prefix_sum_of_binom_randomized.test.cpp
    title: verify/math/prefix_sum_of_binom_randomized.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/prefix_sum_of_binom.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <cstdint>\n#include <numeric>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"math/combinatorics.hpp\"\n\n\
    \n\n#line 7 \"math/combinatorics.hpp\"\n\nnamespace m1une {\nnamespace math {\n\
    \ntemplate <class Mint>\nstruct Combinatorics {\n   private:\n    std::vector<Mint>\
    \ _factorial;\n    std::vector<Mint> _inverse_factorial;\n\n   public:\n    explicit\
    \ Combinatorics(int maximum = 0) : _factorial(1, Mint(1)), _inverse_factorial(1,\
    \ Mint(1)) {\n        ensure(maximum);\n    }\n\n    int maximum() const {\n \
    \       return int(_factorial.size()) - 1;\n    }\n\n    void ensure(int maximum)\
    \ {\n        assert(maximum >= 0);\n        assert(static_cast<uint64_t>(maximum)\
    \ < Mint::mod());\n        if (maximum <= this->maximum()) return;\n\n       \
    \ const int old_maximum = this->maximum();\n        _factorial.resize(maximum\
    \ + 1);\n        _inverse_factorial.resize(maximum + 1);\n        for (int i =\
    \ old_maximum + 1; i <= maximum; i++) {\n            _factorial[i] = _factorial[i\
    \ - 1] * Mint(i);\n        }\n        _inverse_factorial[maximum] = _factorial[maximum].inv();\n\
    \        for (int i = maximum; i > old_maximum; i--) {\n            _inverse_factorial[i\
    \ - 1] = _inverse_factorial[i] * Mint(i);\n        }\n    }\n\n    Mint factorial(int\
    \ n) const {\n        assert(0 <= n && n <= maximum());\n        return _factorial[n];\n\
    \    }\n\n    Mint inverse_factorial(int n) const {\n        assert(0 <= n &&\
    \ n <= maximum());\n        return _inverse_factorial[n];\n    }\n\n    Mint inverse(int\
    \ n) const {\n        assert(1 <= n && n <= maximum());\n        return _factorial[n\
    \ - 1] * _inverse_factorial[n];\n    }\n\n    Mint binom(int n, int k) const {\n\
    \        if (k < 0 || k > n) return Mint(0);\n        assert(n <= maximum());\n\
    \        return _factorial[n] * _inverse_factorial[k] * _inverse_factorial[n -\
    \ k];\n    }\n\n    Mint perm(int n, int k) const {\n        if (k < 0 || k >\
    \ n) return Mint(0);\n        assert(n <= maximum());\n        return _factorial[n]\
    \ * _inverse_factorial[n - k];\n    }\n\n    Mint multiset(int types, int count)\
    \ const {\n        if (types < 0 || count < 0) return Mint(0);\n        if (types\
    \ == 0) return Mint(count == 0);\n        const long long total = static_cast<long\
    \ long>(types) + count - 1;\n        assert(total <= maximum());\n        return\
    \ binom(static_cast<int>(total), count);\n    }\n\n    Mint catalan(int n) const\
    \ {\n        assert(n >= 0);\n        const long long doubled = 2LL * n;\n   \
    \     assert(doubled <= maximum());\n        return binom(int(doubled), n) - binom(int(doubled),\
    \ n + 1);\n    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line\
    \ 13 \"math/prefix_sum_of_binom.hpp\"\n\nnamespace m1une {\nnamespace math {\n\
    \n// Answers sum_{k=0}^{m-1} binom(n, k) after square-root decomposition.\ntemplate\
    \ <class Mint>\nstruct PrefixSumOfBinom {\n   private:\n    int _maximum;\n  \
    \  int _block_size;\n    Combinatorics<Mint> _combinations;\n    std::vector<Mint>\
    \ _powers_of_two;\n    std::vector<std::vector<Mint>> _data;\n\n    Mint _block_prefix(int\
    \ n, int block) const {\n        const int endpoint = block * _block_size;\n \
    \       if (n <= endpoint) return _powers_of_two[n];\n        return _data[block][n\
    \ - endpoint] * _combinations.inverse_factorial(endpoint);\n    }\n\n    Mint\
    \ _binom_sum(int n, int left, int right) const {\n        __uint128_t sum = 0;\n\
    \        for (int k = left; k < right; k++) {\n            sum += static_cast<__uint128_t>(_combinations.inverse_factorial(k).val())\
    \ *\n                   _combinations.inverse_factorial(n - k).val();\n      \
    \  }\n        const uint32_t reduced = static_cast<uint32_t>(sum % Mint::mod());\n\
    \        return Mint::raw(reduced) * _combinations.factorial(n);\n    }\n\n  \
    \ public:\n    explicit PrefixSumOfBinom(int maximum)\n        : _maximum(maximum),\n\
    \          _block_size(std::max(1, int(std::sqrt(static_cast<double>(maximum)\
    \ + 1)))),\n          _combinations(maximum),\n          _powers_of_two(maximum\
    \ + 1, Mint(1)) {\n        assert(maximum >= 0);\n\n        for (int n = 0; n\
    \ < maximum; n++) {\n            _powers_of_two[n + 1] = _powers_of_two[n] + _powers_of_two[n];\n\
    \        }\n\n        const int block_count = maximum / (2 * _block_size) + 3;\n\
    \        _data.resize(block_count);\n        for (int block = 0; block < block_count;\
    \ block++) {\n            const int endpoint = block * _block_size;\n        \
    \    if (endpoint > maximum) continue;\n\n            std::vector<Mint>& values\
    \ = _data[block];\n            values.resize(maximum - endpoint + 1);\n      \
    \      values[0] = _powers_of_two[endpoint] * _combinations.factorial(endpoint);\n\
    \            for (int offset = 0; offset < maximum - endpoint; offset++) {\n \
    \               values[offset + 1] =\n                    values[offset] + values[offset]\
    \ -\n                    _combinations.factorial(offset + endpoint) *\n      \
    \                  _combinations.inverse_factorial(offset);\n            }\n \
    \       }\n    }\n\n    int maximum() const {\n        return _maximum;\n    }\n\
    \n    // Returns sum_{k=0}^{m-1} binom(n, k). Values m > n + 1 are clamped.\n\
    \    Mint query(int n, int m) const {\n        assert(0 <= n && n <= _maximum);\n\
    \        assert(m >= 0);\n        m = std::min(m, n + 1);\n        if (m == 0)\
    \ return Mint(0);\n        if (2 * m > n + 1) {\n            return _powers_of_two[n]\
    \ - query(n, n + 1 - m);\n        }\n\n        const int endpoint = m - 1;\n \
    \       const int block = endpoint / _block_size;\n        const int lower = block\
    \ * _block_size;\n        const int upper = (block + 1) * _block_size;\n     \
    \   if (endpoint - lower <= upper - endpoint) {\n            return _block_prefix(n,\
    \ block) + _binom_sum(n, lower + 1, endpoint + 1);\n        }\n        return\
    \ _block_prefix(n, block + 1) - _binom_sum(n, endpoint + 1, upper + 1);\n    }\n\
    };\n\n// Batches the same queries and evaluates them in Mo order with linear memory.\n\
    template <class Mint>\nstruct OfflinePrefixSumOfBinom {\n   private:\n    std::vector<std::pair<int,\
    \ int>> _queries;\n\n   public:\n    int query_count() const {\n        return\
    \ int(_queries.size());\n    }\n\n    bool empty() const {\n        return _queries.empty();\n\
    \    }\n\n    void reserve(int query_capacity) {\n        assert(query_capacity\
    \ >= 0);\n        _queries.reserve(query_capacity);\n    }\n\n    void clear()\
    \ {\n        _queries.clear();\n    }\n\n    // Adds sum_{k=0}^{m-1} binom(n,\
    \ k) and returns its insertion-order ID.\n    int add_query(int n, int m) {\n\
    \        assert(n >= 0);\n        assert(m >= 0);\n        m = std::min(m, n +\
    \ 1);\n        const int id = query_count();\n        _queries.emplace_back(n,\
    \ m);\n        return id;\n    }\n\n    std::vector<Mint> calculate() const {\n\
    \        const int count = query_count();\n        std::vector<Mint> answers(count);\n\
    \        if (count == 0) return answers;\n\n        int maximum = 0;\n       \
    \ for (const auto& query : _queries) maximum = std::max(maximum, query.first);\n\
    \        assert(static_cast<uint64_t>(maximum) < Mint::mod());\n        assert(Mint::mod()\
    \ % 2 == 1);\n        Combinatorics<Mint> combinations(maximum);\n\n        const\
    \ int block_size =\n            std::max(1, int(maximum / std::sqrt(static_cast<double>(count))));\n\
    \        std::vector<int> order(count);\n        std::iota(order.begin(), order.end(),\
    \ 0);\n        std::sort(order.begin(), order.end(), [&](int first, int second)\
    \ {\n            const int first_block = _queries[first].first / block_size;\n\
    \            const int second_block = _queries[second].first / block_size;\n \
    \           if (first_block != second_block) return first_block < second_block;\n\
    \            if (first_block & 1) return _queries[first].second > _queries[second].second;\n\
    \            return _queries[first].second < _queries[second].second;\n      \
    \  });\n\n        int n = 0;\n        int m = 0;\n        Mint answer = 0;\n \
    \       const Mint inverse_two = Mint(2).inv();\n        for (int id : order)\
    \ {\n            const int next_n = _queries[id].first;\n            const int\
    \ next_m = _queries[id].second;\n            while (n < next_n) {\n          \
    \      answer += answer;\n                answer -= combinations.binom(n, m -\
    \ 1);\n                n++;\n            }\n            while (n > next_n) {\n\
    \                answer += combinations.binom(n - 1, m - 1);\n               \
    \ answer *= inverse_two;\n                n--;\n            }\n            while\
    \ (m < next_m) answer += combinations.binom(n, m++);\n            while (m > next_m)\
    \ answer -= combinations.binom(n, --m);\n            answers[id] = answer;\n \
    \       }\n        return answers;\n    }\n};\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_PREFIX_SUM_OF_BINOM_HPP\n#define M1UNE_MATH_PREFIX_SUM_OF_BINOM_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <cstdint>\n\
    #include <numeric>\n#include <utility>\n#include <vector>\n\n#include \"combinatorics.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\n// Answers sum_{k=0}^{m-1} binom(n,\
    \ k) after square-root decomposition.\ntemplate <class Mint>\nstruct PrefixSumOfBinom\
    \ {\n   private:\n    int _maximum;\n    int _block_size;\n    Combinatorics<Mint>\
    \ _combinations;\n    std::vector<Mint> _powers_of_two;\n    std::vector<std::vector<Mint>>\
    \ _data;\n\n    Mint _block_prefix(int n, int block) const {\n        const int\
    \ endpoint = block * _block_size;\n        if (n <= endpoint) return _powers_of_two[n];\n\
    \        return _data[block][n - endpoint] * _combinations.inverse_factorial(endpoint);\n\
    \    }\n\n    Mint _binom_sum(int n, int left, int right) const {\n        __uint128_t\
    \ sum = 0;\n        for (int k = left; k < right; k++) {\n            sum += static_cast<__uint128_t>(_combinations.inverse_factorial(k).val())\
    \ *\n                   _combinations.inverse_factorial(n - k).val();\n      \
    \  }\n        const uint32_t reduced = static_cast<uint32_t>(sum % Mint::mod());\n\
    \        return Mint::raw(reduced) * _combinations.factorial(n);\n    }\n\n  \
    \ public:\n    explicit PrefixSumOfBinom(int maximum)\n        : _maximum(maximum),\n\
    \          _block_size(std::max(1, int(std::sqrt(static_cast<double>(maximum)\
    \ + 1)))),\n          _combinations(maximum),\n          _powers_of_two(maximum\
    \ + 1, Mint(1)) {\n        assert(maximum >= 0);\n\n        for (int n = 0; n\
    \ < maximum; n++) {\n            _powers_of_two[n + 1] = _powers_of_two[n] + _powers_of_two[n];\n\
    \        }\n\n        const int block_count = maximum / (2 * _block_size) + 3;\n\
    \        _data.resize(block_count);\n        for (int block = 0; block < block_count;\
    \ block++) {\n            const int endpoint = block * _block_size;\n        \
    \    if (endpoint > maximum) continue;\n\n            std::vector<Mint>& values\
    \ = _data[block];\n            values.resize(maximum - endpoint + 1);\n      \
    \      values[0] = _powers_of_two[endpoint] * _combinations.factorial(endpoint);\n\
    \            for (int offset = 0; offset < maximum - endpoint; offset++) {\n \
    \               values[offset + 1] =\n                    values[offset] + values[offset]\
    \ -\n                    _combinations.factorial(offset + endpoint) *\n      \
    \                  _combinations.inverse_factorial(offset);\n            }\n \
    \       }\n    }\n\n    int maximum() const {\n        return _maximum;\n    }\n\
    \n    // Returns sum_{k=0}^{m-1} binom(n, k). Values m > n + 1 are clamped.\n\
    \    Mint query(int n, int m) const {\n        assert(0 <= n && n <= _maximum);\n\
    \        assert(m >= 0);\n        m = std::min(m, n + 1);\n        if (m == 0)\
    \ return Mint(0);\n        if (2 * m > n + 1) {\n            return _powers_of_two[n]\
    \ - query(n, n + 1 - m);\n        }\n\n        const int endpoint = m - 1;\n \
    \       const int block = endpoint / _block_size;\n        const int lower = block\
    \ * _block_size;\n        const int upper = (block + 1) * _block_size;\n     \
    \   if (endpoint - lower <= upper - endpoint) {\n            return _block_prefix(n,\
    \ block) + _binom_sum(n, lower + 1, endpoint + 1);\n        }\n        return\
    \ _block_prefix(n, block + 1) - _binom_sum(n, endpoint + 1, upper + 1);\n    }\n\
    };\n\n// Batches the same queries and evaluates them in Mo order with linear memory.\n\
    template <class Mint>\nstruct OfflinePrefixSumOfBinom {\n   private:\n    std::vector<std::pair<int,\
    \ int>> _queries;\n\n   public:\n    int query_count() const {\n        return\
    \ int(_queries.size());\n    }\n\n    bool empty() const {\n        return _queries.empty();\n\
    \    }\n\n    void reserve(int query_capacity) {\n        assert(query_capacity\
    \ >= 0);\n        _queries.reserve(query_capacity);\n    }\n\n    void clear()\
    \ {\n        _queries.clear();\n    }\n\n    // Adds sum_{k=0}^{m-1} binom(n,\
    \ k) and returns its insertion-order ID.\n    int add_query(int n, int m) {\n\
    \        assert(n >= 0);\n        assert(m >= 0);\n        m = std::min(m, n +\
    \ 1);\n        const int id = query_count();\n        _queries.emplace_back(n,\
    \ m);\n        return id;\n    }\n\n    std::vector<Mint> calculate() const {\n\
    \        const int count = query_count();\n        std::vector<Mint> answers(count);\n\
    \        if (count == 0) return answers;\n\n        int maximum = 0;\n       \
    \ for (const auto& query : _queries) maximum = std::max(maximum, query.first);\n\
    \        assert(static_cast<uint64_t>(maximum) < Mint::mod());\n        assert(Mint::mod()\
    \ % 2 == 1);\n        Combinatorics<Mint> combinations(maximum);\n\n        const\
    \ int block_size =\n            std::max(1, int(maximum / std::sqrt(static_cast<double>(count))));\n\
    \        std::vector<int> order(count);\n        std::iota(order.begin(), order.end(),\
    \ 0);\n        std::sort(order.begin(), order.end(), [&](int first, int second)\
    \ {\n            const int first_block = _queries[first].first / block_size;\n\
    \            const int second_block = _queries[second].first / block_size;\n \
    \           if (first_block != second_block) return first_block < second_block;\n\
    \            if (first_block & 1) return _queries[first].second > _queries[second].second;\n\
    \            return _queries[first].second < _queries[second].second;\n      \
    \  });\n\n        int n = 0;\n        int m = 0;\n        Mint answer = 0;\n \
    \       const Mint inverse_two = Mint(2).inv();\n        for (int id : order)\
    \ {\n            const int next_n = _queries[id].first;\n            const int\
    \ next_m = _queries[id].second;\n            while (n < next_n) {\n          \
    \      answer += answer;\n                answer -= combinations.binom(n, m -\
    \ 1);\n                n++;\n            }\n            while (n > next_n) {\n\
    \                answer += combinations.binom(n - 1, m - 1);\n               \
    \ answer *= inverse_two;\n                n--;\n            }\n            while\
    \ (m < next_m) answer += combinations.binom(n, m++);\n            while (m > next_m)\
    \ answer -= combinations.binom(n, --m);\n            answers[id] = answer;\n \
    \       }\n        return answers;\n    }\n};\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MATH_PREFIX_SUM_OF_BINOM_HPP\n"
  dependsOn:
  - math/combinatorics.hpp
  isVerificationFile: false
  path: math/prefix_sum_of_binom.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-13 03:08:36+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/math/prefix_sum_of_binom.test.cpp
  - verify/math/math_algorithms.test.cpp
  - verify/math/prefix_sum_of_binom_randomized.test.cpp
documentation_of: math/prefix_sum_of_binom.hpp
layout: document
title: Prefix Sum of Binomial Coefficients
---

## Overview

`PrefixSumOfBinom<Mint>` and `OfflinePrefixSumOfBinom<Mint>` compute

$$
\sum_{k=0}^{m-1} \binom{n}{k}.
$$

The online structure is useful when queries must be answered immediately. It
precomputes binomial-prefix values at square-root-spaced endpoints. The offline
structure stores all queries and moves between them in Mo order, using Pascal's
identity to update the current answer.

`Mint` must provide the static-modulus interface used by `ModInt`. The modulus
must be prime, odd for the offline structure, and larger than every queried
`n`.

## API

```cpp
template <class Mint>
struct PrefixSumOfBinom {
    explicit PrefixSumOfBinom(int maximum);
    int maximum() const;
    Mint query(int n, int m) const;
};

template <class Mint>
struct OfflinePrefixSumOfBinom {
    int query_count() const;
    bool empty() const;
    void reserve(int query_capacity);
    void clear();
    int add_query(int n, int m);
    std::vector<Mint> calculate() const;
};
```

| Method | Description | Complexity |
| --- | --- | --- |
| `PrefixSumOfBinom(maximum)` | Precomputes data for every `0 <= n <= maximum`. | $O(N\sqrt N)$ time and memory |
| `maximum()` | Returns the largest supported `n`. | $O(1)$ |
| `query(n, m)` | Returns the half-open prefix through `m - 1`. | $O(\sqrt N)$ |
| `query_count()` | Returns the number of stored offline queries. | $O(1)$ |
| `empty()` | Tests whether the offline batch is empty. | $O(1)$ |
| `reserve(query_capacity)` | Reserves storage for offline queries. | $O(Q)$ in the worst case |
| `clear()` | Removes all offline queries. | $O(Q)$ |
| `add_query(n, m)` | Stores a query and returns its insertion-order ID. | Amortized $O(1)$ |
| `calculate()` | Returns answers in insertion order. | $O((N+Q)\sqrt Q)$ time and $O(N+Q)$ memory |

Here $N$ is the largest queried or constructed `n`, and $Q$ is the number of
offline queries.

## Behavioral Notes

* The range in `k` is half-open: `query(n, m)` sums `0 <= k < m`.
* `m == 0` returns zero.
* Values `m > n + 1` are clamped to `n + 1`, so the result is `2^n`.
* The online constructor asserts that `maximum` is nonnegative and smaller than
  the modulus. Each query asserts `0 <= n <= maximum` and `m >= 0`.
* `calculate()` does not clear or mutate the offline query batch. Query IDs and
  returned positions use insertion order.
* The online version has relatively high memory use. Prefer the offline version
  when all queries are known beforehand.

## Example

```cpp
#include "math/modint.hpp"
#include "math/prefix_sum_of_binom.hpp"

#include <iostream>

int main() {
    using Mint = m1une::math::modint998244353;
    m1une::math::PrefixSumOfBinom<Mint> prefix(1000);

    // 1 + 5 + 10 = 16
    std::cout << prefix.query(5, 3) << '\n';

    m1une::math::OfflinePrefixSumOfBinom<Mint> offline;
    offline.add_query(5, 3);
    offline.add_query(4, 5);
    const auto answers = offline.calculate();
    std::cout << answers[0] << ' ' << answers[1] << '\n';
}
```
