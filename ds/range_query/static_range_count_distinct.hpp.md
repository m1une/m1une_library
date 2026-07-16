---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/wavelet_matrix/wavelet_matrix.hpp
    title: Wavelet Matrix
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/static_range_count_distinct.test.cpp
    title: verify/ds/range_query/static_range_count_distinct.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/static_range_count_distinct.hpp\"\n\n\n\n\
    #line 1 \"ds/wavelet_matrix/wavelet_matrix.hpp\"\n\n\n\n#include <bit>\n#include\
    \ <cassert>\n#include <concepts>\n#include <cstdint>\n#include <limits>\n#include\
    \ <optional>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\n\
    namespace m1une {\nnamespace ds {\n\n// A static wavelet matrix for integral values.\n\
    template <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\n\
    struct WaveletMatrix {\n    using value_type = T;\n    using unsigned_type = std::make_unsigned_t<T>;\n\
    \n   private:\n    static constexpr int value_bit_width =\n        std::numeric_limits<unsigned_type>::digits;\n\
    \    static constexpr unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
    \ {\n            return unsigned_type(1) << (value_bit_width - 1);\n        }\
    \ else {\n            return unsigned_type(0);\n        }\n    }();\n\n    struct\
    \ BitVector {\n        std::vector<std::uint64_t> bits;\n        std::vector<int>\
    \ prefix;\n\n        BitVector() = default;\n\n        explicit BitVector(int\
    \ n)\n            : bits((std::size_t(n) + 63) >> 6, 0),\n              prefix(bits.size()\
    \ + 1, 0) {}\n\n        void set(int p) {\n            bits[std::size_t(p) >>\
    \ 6] |= std::uint64_t(1) << (p & 63);\n        }\n\n        void build() {\n \
    \           for (std::size_t i = 0; i < bits.size(); i++) {\n                prefix[i\
    \ + 1] = prefix[i] + std::popcount(bits[i]);\n            }\n        }\n\n   \
    \     bool get(int p) const {\n            return (bits[std::size_t(p) >> 6] >>\
    \ (p & 63)) & 1;\n        }\n\n        int rank1(int r) const {\n            std::size_t\
    \ word = std::size_t(r) >> 6;\n            int offset = r & 63;\n            int\
    \ result = prefix[word];\n            if (offset != 0) {\n                result\
    \ += std::popcount(\n                    bits[word] & ((std::uint64_t(1) << offset)\
    \ - 1)\n                );\n            }\n            return result;\n      \
    \  }\n    };\n\n    int _n;\n    int _log;\n    unsigned_type _key_prefix;\n \
    \   unsigned_type _min_key;\n    unsigned_type _max_key;\n    std::vector<BitVector>\
    \ _matrix;\n    std::vector<int> _zero_count;\n\n    static unsigned_type encode(T\
    \ value) {\n        unsigned_type bits;\n        if constexpr (std::signed_integral<T>)\
    \ {\n            bits = std::bit_cast<unsigned_type>(value);\n        } else {\n\
    \            bits = value;\n        }\n        return bits ^ sign_mask;\n    }\n\
    \n    static T decode(unsigned_type key) {\n        unsigned_type bits = key ^\
    \ sign_mask;\n        if constexpr (std::signed_integral<T>) {\n            return\
    \ std::bit_cast<T>(bits);\n        } else {\n            return bits;\n      \
    \  }\n    }\n\n    bool bit(unsigned_type value, int level) const {\n        return\
    \ (value >> (_log - 1 - level)) & unsigned_type(1);\n    }\n\n    int count_less_encoded(int\
    \ l, int r, unsigned_type upper) const {\n        if (_n == 0 || upper <= _min_key)\
    \ return 0;\n        if (upper > _max_key) return r - l;\n\n        int result\
    \ = 0;\n        for (int level = 0; level < _log; level++) {\n            int\
    \ l1 = _matrix[level].rank1(l);\n            int r1 = _matrix[level].rank1(r);\n\
    \            if (bit(upper, level)) {\n                result += (r - l) - (r1\
    \ - l1);\n                l = _zero_count[level] + l1;\n                r = _zero_count[level]\
    \ + r1;\n            } else {\n                l -= l1;\n                r -=\
    \ r1;\n            }\n        }\n        return result;\n    }\n\n   public:\n\
    \    WaveletMatrix()\n        : _n(0),\n          _log(0),\n          _key_prefix(0),\n\
    \          _min_key(0),\n          _max_key(0) {}\n\n    explicit WaveletMatrix(const\
    \ std::vector<T>& values)\n        : _n(int(values.size())),\n          _log(0),\n\
    \          _key_prefix(0),\n          _min_key(0),\n          _max_key(0) {\n\
    \        std::vector<unsigned_type> current(_n);\n        std::vector<unsigned_type>\
    \ next(_n);\n        for (int i = 0; i < _n; i++) current[i] = encode(values[i]);\n\
    \        if (_n == 0) return;\n\n        _min_key = current[0];\n        _max_key\
    \ = current[0];\n        for (unsigned_type key : current) {\n            if (key\
    \ < _min_key) _min_key = key;\n            if (_max_key < key) _max_key = key;\n\
    \        }\n        _log = int(std::bit_width(unsigned_type(_min_key ^ _max_key)));\n\
    \        if (_log != value_bit_width) {\n            _key_prefix = (_min_key >>\
    \ _log) << _log;\n        }\n        _zero_count.assign(_log, 0);\n\n        _matrix.reserve(_log);\n\
    \        for (int level = 0; level < _log; level++) {\n            _matrix.emplace_back(_n);\n\
    \            int zeros = 0;\n            for (int i = 0; i < _n; i++) {\n    \
    \            if (bit(current[i], level)) {\n                    _matrix.back().set(i);\n\
    \                } else {\n                    zeros++;\n                }\n \
    \           }\n            _matrix.back().build();\n\n            _zero_count[level]\
    \ = zeros;\n            int zero_pos = 0;\n            int one_pos = zeros;\n\
    \            for (unsigned_type value : current) {\n                if (bit(value,\
    \ level)) {\n                    next[one_pos++] = value;\n                } else\
    \ {\n                    next[zero_pos++] = value;\n                }\n      \
    \      }\n            current.swap(next);\n        }\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    T access(int p) const {\n        assert(0 <= p && p <\
    \ _n);\n        unsigned_type key = _key_prefix;\n        for (int level = 0;\
    \ level < _log; level++) {\n            int ones_before = _matrix[level].rank1(p);\n\
    \            bool one = _matrix[level].get(p);\n            if (one) {\n     \
    \           key |= unsigned_type(1) << (_log - 1 - level);\n                p\
    \ = _zero_count[level] + ones_before;\n            } else {\n                p\
    \ -= ones_before;\n            }\n        }\n        return decode(key);\n   \
    \ }\n\n    T operator[](int p) const {\n        return access(p);\n    }\n\n \
    \   int rank(T value, int r) const {\n        assert(0 <= r && r <= _n);\n   \
    \     return rank(value, 0, r);\n    }\n\n    int rank(T value, int l, int r)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        unsigned_type\
    \ key = encode(value);\n        if (_n == 0 || key < _min_key || _max_key < key)\
    \ return 0;\n        for (int level = 0; level < _log; level++) {\n          \
    \  int l1 = _matrix[level].rank1(l);\n            int r1 = _matrix[level].rank1(r);\n\
    \            if (bit(key, level)) {\n                l = _zero_count[level] +\
    \ l1;\n                r = _zero_count[level] + r1;\n            } else {\n  \
    \              l -= l1;\n                r -= r1;\n            }\n        }\n\
    \        return r - l;\n    }\n\n    T kth_smallest(int l, int r, int k) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        assert(0 <= k && k\
    \ < r - l);\n        unsigned_type key = _key_prefix;\n        for (int level\
    \ = 0; level < _log; level++) {\n            int l1 = _matrix[level].rank1(l);\n\
    \            int r1 = _matrix[level].rank1(r);\n            int l0 = l - l1;\n\
    \            int r0 = r - r1;\n            int zeros = r0 - l0;\n            if\
    \ (k < zeros) {\n                l = l0;\n                r = r0;\n          \
    \  } else {\n                k -= zeros;\n                key |= unsigned_type(1)\
    \ << (_log - 1 - level);\n                l = _zero_count[level] + l1;\n     \
    \           r = _zero_count[level] + r1;\n            }\n        }\n        return\
    \ decode(key);\n    }\n\n    T kth_largest(int l, int r, int k) const {\n    \
    \    assert(0 <= l && l <= r && r <= _n);\n        assert(0 <= k && k < r - l);\n\
    \        return kth_smallest(l, r, r - l - 1 - k);\n    }\n\n    int range_freq(int\
    \ l, int r, T upper) const {\n        assert(0 <= l && l <= r && r <= _n);\n \
    \       return count_less_encoded(l, r, encode(upper));\n    }\n\n    int range_freq(int\
    \ l, int r, T lower, T upper) const {\n        assert(0 <= l && l <= r && r <=\
    \ _n);\n        if (upper <= lower) return 0;\n        return range_freq(l, r,\
    \ upper) - range_freq(l, r, lower);\n    }\n\n    std::optional<T> prev_value(int\
    \ l, int r, T upper) const {\n        assert(0 <= l && l <= r && r <= _n);\n \
    \       int count = range_freq(l, r, upper);\n        if (count == 0) return std::nullopt;\n\
    \        return kth_smallest(l, r, count - 1);\n    }\n\n    std::optional<T>\
    \ next_value(int l, int r, T lower) const {\n        assert(0 <= l && l <= r &&\
    \ r <= _n);\n        int count = range_freq(l, r, lower);\n        if (count ==\
    \ r - l) return std::nullopt;\n        return kth_smallest(l, r, count);\n   \
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 5 \"ds/range_query/static_range_count_distinct.hpp\"\
    \n\n#include <algorithm>\n#line 9 \"ds/range_query/static_range_count_distinct.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Counts distinct values in static half-open\
    \ ranges.\ntemplate <class T>\nstruct StaticRangeCountDistinct {\n   private:\n\
    \    int _n;\n    WaveletMatrix<int> _previous;\n\n   public:\n    StaticRangeCountDistinct()\
    \ : _n(0), _previous() {}\n\n    explicit StaticRangeCountDistinct(const std::vector<T>&\
    \ values)\n        : _n(int(values.size())), _previous() {\n        if (_n ==\
    \ 0) return;\n\n        std::vector<T> compressed = values;\n        std::sort(compressed.begin(),\
    \ compressed.end());\n        compressed.erase(\n            std::unique(compressed.begin(),\
    \ compressed.end()),\n            compressed.end()\n        );\n\n        std::vector<int>\
    \ last(compressed.size(), -1);\n        std::vector<int> previous(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            int rank = int(\n            \
    \    std::lower_bound(\n                    compressed.begin(),\n            \
    \        compressed.end(),\n                    values[i]\n                ) -\
    \ compressed.begin()\n            );\n            previous[i] = last[rank];\n\
    \            last[rank] = i;\n        }\n        _previous = WaveletMatrix<int>(previous);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int query(int left, int right)\
    \ const {\n        assert(0 <= left && left <= right && right <= _n);\n      \
    \  if (left == right) return 0;\n        return _previous.range_freq(left, right,\
    \ left);\n    }\n\n    int count_distinct(int left, int right) const {\n     \
    \   return query(left, right);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_STATIC_RANGE_COUNT_DISTINCT_HPP\n#define M1UNE_DS_RANGE_QUERY_STATIC_RANGE_COUNT_DISTINCT_HPP\
    \ 1\n\n#include \"../wavelet_matrix/wavelet_matrix.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    // Counts distinct values in static half-open ranges.\ntemplate <class T>\nstruct\
    \ StaticRangeCountDistinct {\n   private:\n    int _n;\n    WaveletMatrix<int>\
    \ _previous;\n\n   public:\n    StaticRangeCountDistinct() : _n(0), _previous()\
    \ {}\n\n    explicit StaticRangeCountDistinct(const std::vector<T>& values)\n\
    \        : _n(int(values.size())), _previous() {\n        if (_n == 0) return;\n\
    \n        std::vector<T> compressed = values;\n        std::sort(compressed.begin(),\
    \ compressed.end());\n        compressed.erase(\n            std::unique(compressed.begin(),\
    \ compressed.end()),\n            compressed.end()\n        );\n\n        std::vector<int>\
    \ last(compressed.size(), -1);\n        std::vector<int> previous(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            int rank = int(\n            \
    \    std::lower_bound(\n                    compressed.begin(),\n            \
    \        compressed.end(),\n                    values[i]\n                ) -\
    \ compressed.begin()\n            );\n            previous[i] = last[rank];\n\
    \            last[rank] = i;\n        }\n        _previous = WaveletMatrix<int>(previous);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int query(int left, int right)\
    \ const {\n        assert(0 <= left && left <= right && right <= _n);\n      \
    \  if (left == right) return 0;\n        return _previous.range_freq(left, right,\
    \ left);\n    }\n\n    int count_distinct(int left, int right) const {\n     \
    \   return query(left, right);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_STATIC_RANGE_COUNT_DISTINCT_HPP\n"
  dependsOn:
  - ds/wavelet_matrix/wavelet_matrix.hpp
  isVerificationFile: false
  path: ds/range_query/static_range_count_distinct.hpp
  requiredBy: []
  timestamp: '2026-07-16 18:16:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/static_range_count_distinct.test.cpp
documentation_of: ds/range_query/static_range_count_distinct.hpp
layout: document
title: Static Range Count Distinct
---

## Overview

`StaticRangeCountDistinct<T>` counts the number of distinct values in any
half-open subarray `[left, right)` of a static array.

For every position, the structure records the previous position containing the
same value. A position is the first occurrence of its value inside a query
exactly when its previous occurrence is before `left`. These two-dimensional
counting queries are answered by a wavelet matrix.

## Requirements

`T` must support `<` as a strict weak ordering. Duplicate values and empty
ranges are supported. The input array is not modified.

## Complexity

| Operation | Time | Memory |
| --- | --- | --- |
| Construction | $O(N\log N)$ | $O(N\log N)$ bits |
| Query | $O(\log N)$ | $O(1)$ |

## Methods

| Method | Complexity | Description |
| --- | --- | --- |
| `StaticRangeCountDistinct()` | $O(1)$ | Constructs an empty structure. |
| `explicit StaticRangeCountDistinct(const std::vector<T>& values)` | $O(N\log N)$ | Builds the static structure. |
| `int query(int left, int right) const` | $O(\log N)$ | Counts distinct values in `[left, right)`. |
| `int count_distinct(int left, int right) const` | $O(\log N)$ | Alias of `query`. |
| `int size() const` | $O(1)$ | Returns the array size. |
| `bool empty() const` | $O(1)$ | Returns whether the array is empty. |

## Example

```cpp
#include "ds/range_query/static_range_count_distinct.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {1, 2, 1, 3, 2};
    m1une::ds::StaticRangeCountDistinct<int> distinct(values);

    std::cout << distinct.query(0, 5) << "\n"; // 3
    std::cout << distinct.query(1, 4) << "\n"; // 3
    std::cout << distinct.query(2, 2) << "\n"; // 0
}
```
