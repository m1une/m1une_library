---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/static_range_mode_query.test.cpp
    title: verify/ds/range_query/static_range_mode_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/static_range_mode_query.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cmath>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// Static range modes with\
    \ O(N sqrt N) preprocessing and O(sqrt N) queries.\ntemplate <class T>\nstruct\
    \ StaticRangeModeQuery {\n    using result_type = std::pair<T, int>;\n\n   private:\n\
    \    int _n;\n    int _block_size;\n    int _block_count;\n    std::vector<T>\
    \ _values;\n    std::vector<int> _rank;\n    std::vector<std::vector<int>> _boundary_frequency;\n\
    \    std::vector<std::vector<int>> _mode;\n    std::vector<std::vector<int>> _mode_frequency;\n\
    \    std::vector<int> _extra_frequency;\n    std::vector<unsigned int> _seen_at;\n\
    \    unsigned int _query_time;\n\n    int block_start(int block) const {\n   \
    \     return std::min(_n, block * _block_size);\n    }\n\n    void build_boundary_frequency()\
    \ {\n        int value_count = int(_values.size());\n        _boundary_frequency.assign(\n\
    \            _block_count + 1,\n            std::vector<int>(value_count, 0)\n\
    \        );\n        for (int block = 0; block < _block_count; block++) {\n  \
    \          _boundary_frequency[block + 1] = _boundary_frequency[block];\n    \
    \        for (\n                int i = block_start(block);\n                i\
    \ < block_start(block + 1);\n                i++\n            ) {\n          \
    \      _boundary_frequency[block + 1][_rank[i]]++;\n            }\n        }\n\
    \    }\n\n    void build_block_modes() {\n        int value_count = int(_values.size());\n\
    \        _mode.assign(\n            _block_count,\n            std::vector<int>(_block_count\
    \ + 1, -1)\n        );\n        _mode_frequency.assign(\n            _block_count,\n\
    \            std::vector<int>(_block_count + 1, 0)\n        );\n\n        std::vector<int>\
    \ frequency(value_count, 0);\n        for (int first = 0; first < _block_count;\
    \ first++) {\n            std::fill(frequency.begin(), frequency.end(), 0);\n\
    \            int best = -1;\n            int best_frequency = 0;\n           \
    \ for (int last = first; last < _block_count; last++) {\n                for (\n\
    \                    int i = block_start(last);\n                    i < block_start(last\
    \ + 1);\n                    i++\n                ) {\n                    int\
    \ value = _rank[i];\n                    frequency[value]++;\n               \
    \     if (frequency[value] > best_frequency) {\n                        best =\
    \ value;\n                        best_frequency = frequency[value];\n       \
    \             }\n                }\n                _mode[first][last + 1] = best;\n\
    \                _mode_frequency[first][last + 1] = best_frequency;\n        \
    \    }\n        }\n    }\n\n   public:\n    StaticRangeModeQuery()\n        :\
    \ _n(0),\n          _block_size(1),\n          _block_count(0),\n          _query_time(0)\
    \ {}\n\n    explicit StaticRangeModeQuery(const std::vector<T>& values)\n    \
    \    : _n(int(values.size())),\n          _block_size(1),\n          _block_count(0),\n\
    \          _values(values),\n          _query_time(0) {\n        if (_n == 0)\
    \ return;\n\n        _block_size = std::max(\n            1,\n            int(std::sqrt(static_cast<long\
    \ double>(_n)))\n        );\n        while (1LL * _block_size * _block_size <\
    \ _n) _block_size++;\n        _block_count = (_n + _block_size - 1) / _block_size;\n\
    \n        std::sort(_values.begin(), _values.end());\n        _values.erase(\n\
    \            std::unique(_values.begin(), _values.end()),\n            _values.end()\n\
    \        );\n        _rank.resize(_n);\n        for (int i = 0; i < _n; i++) {\n\
    \            _rank[i] = int(\n                std::lower_bound(_values.begin(),\
    \ _values.end(), values[i])\n                - _values.begin()\n            );\n\
    \        }\n\n        build_boundary_frequency();\n        build_block_modes();\n\
    \        _extra_frequency.assign(_values.size(), 0);\n        _seen_at.assign(_values.size(),\
    \ 0);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int block_size() const\
    \ {\n        return _block_size;\n    }\n\n    // Returns {a mode, its frequency}\
    \ for the nonempty range [left, right).\n    // The method reuses internal scratch\
    \ arrays and is therefore non-const.\n    result_type query(int left, int right)\
    \ {\n        assert(0 <= left && left < right && right <= _n);\n\n        int\
    \ first_full = (left + _block_size - 1) / _block_size;\n        int last_full\
    \ = right / _block_size;\n        int left_end = std::min(right, block_start(first_full));\n\
    \        int right_start = std::max(left_end, block_start(last_full));\n\n   \
    \     int answer = -1;\n        int answer_frequency = 0;\n        if (first_full\
    \ < last_full) {\n            answer = _mode[first_full][last_full];\n       \
    \     answer_frequency = _mode_frequency[first_full][last_full];\n        }\n\n\
    \        _query_time++;\n        if (_query_time == 0) {\n            std::fill(_seen_at.begin(),\
    \ _seen_at.end(), 0);\n            _query_time = 1;\n        }\n        std::vector<int>\
    \ touched;\n        touched.reserve(left_end - left + right - right_start);\n\
    \        auto add = [&](int index) {\n            int value = _rank[index];\n\
    \            if (_seen_at[value] != _query_time) {\n                _seen_at[value]\
    \ = _query_time;\n                _extra_frequency[value] = 0;\n             \
    \   touched.push_back(value);\n            }\n            _extra_frequency[value]++;\n\
    \        };\n        for (int i = left; i < left_end; i++) add(i);\n        for\
    \ (int i = right_start; i < right; i++) add(i);\n\n        for (int value : touched)\
    \ {\n            int frequency = _extra_frequency[value];\n            if (first_full\
    \ < last_full) {\n                frequency +=\n                    _boundary_frequency[last_full][value]\n\
    \                    - _boundary_frequency[first_full][value];\n            }\n\
    \            if (frequency > answer_frequency) {\n                answer = value;\n\
    \                answer_frequency = frequency;\n            }\n        }\n   \
    \     assert(answer != -1);\n        return {_values[answer], answer_frequency};\n\
    \    }\n\n    result_type mode(int left, int right) {\n        return query(left,\
    \ right);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MODE_QUERY_HPP\n#define M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MODE_QUERY_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// Static range modes\
    \ with O(N sqrt N) preprocessing and O(sqrt N) queries.\ntemplate <class T>\n\
    struct StaticRangeModeQuery {\n    using result_type = std::pair<T, int>;\n\n\
    \   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n    std::vector<T>\
    \ _values;\n    std::vector<int> _rank;\n    std::vector<std::vector<int>> _boundary_frequency;\n\
    \    std::vector<std::vector<int>> _mode;\n    std::vector<std::vector<int>> _mode_frequency;\n\
    \    std::vector<int> _extra_frequency;\n    std::vector<unsigned int> _seen_at;\n\
    \    unsigned int _query_time;\n\n    int block_start(int block) const {\n   \
    \     return std::min(_n, block * _block_size);\n    }\n\n    void build_boundary_frequency()\
    \ {\n        int value_count = int(_values.size());\n        _boundary_frequency.assign(\n\
    \            _block_count + 1,\n            std::vector<int>(value_count, 0)\n\
    \        );\n        for (int block = 0; block < _block_count; block++) {\n  \
    \          _boundary_frequency[block + 1] = _boundary_frequency[block];\n    \
    \        for (\n                int i = block_start(block);\n                i\
    \ < block_start(block + 1);\n                i++\n            ) {\n          \
    \      _boundary_frequency[block + 1][_rank[i]]++;\n            }\n        }\n\
    \    }\n\n    void build_block_modes() {\n        int value_count = int(_values.size());\n\
    \        _mode.assign(\n            _block_count,\n            std::vector<int>(_block_count\
    \ + 1, -1)\n        );\n        _mode_frequency.assign(\n            _block_count,\n\
    \            std::vector<int>(_block_count + 1, 0)\n        );\n\n        std::vector<int>\
    \ frequency(value_count, 0);\n        for (int first = 0; first < _block_count;\
    \ first++) {\n            std::fill(frequency.begin(), frequency.end(), 0);\n\
    \            int best = -1;\n            int best_frequency = 0;\n           \
    \ for (int last = first; last < _block_count; last++) {\n                for (\n\
    \                    int i = block_start(last);\n                    i < block_start(last\
    \ + 1);\n                    i++\n                ) {\n                    int\
    \ value = _rank[i];\n                    frequency[value]++;\n               \
    \     if (frequency[value] > best_frequency) {\n                        best =\
    \ value;\n                        best_frequency = frequency[value];\n       \
    \             }\n                }\n                _mode[first][last + 1] = best;\n\
    \                _mode_frequency[first][last + 1] = best_frequency;\n        \
    \    }\n        }\n    }\n\n   public:\n    StaticRangeModeQuery()\n        :\
    \ _n(0),\n          _block_size(1),\n          _block_count(0),\n          _query_time(0)\
    \ {}\n\n    explicit StaticRangeModeQuery(const std::vector<T>& values)\n    \
    \    : _n(int(values.size())),\n          _block_size(1),\n          _block_count(0),\n\
    \          _values(values),\n          _query_time(0) {\n        if (_n == 0)\
    \ return;\n\n        _block_size = std::max(\n            1,\n            int(std::sqrt(static_cast<long\
    \ double>(_n)))\n        );\n        while (1LL * _block_size * _block_size <\
    \ _n) _block_size++;\n        _block_count = (_n + _block_size - 1) / _block_size;\n\
    \n        std::sort(_values.begin(), _values.end());\n        _values.erase(\n\
    \            std::unique(_values.begin(), _values.end()),\n            _values.end()\n\
    \        );\n        _rank.resize(_n);\n        for (int i = 0; i < _n; i++) {\n\
    \            _rank[i] = int(\n                std::lower_bound(_values.begin(),\
    \ _values.end(), values[i])\n                - _values.begin()\n            );\n\
    \        }\n\n        build_boundary_frequency();\n        build_block_modes();\n\
    \        _extra_frequency.assign(_values.size(), 0);\n        _seen_at.assign(_values.size(),\
    \ 0);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int block_size() const\
    \ {\n        return _block_size;\n    }\n\n    // Returns {a mode, its frequency}\
    \ for the nonempty range [left, right).\n    // The method reuses internal scratch\
    \ arrays and is therefore non-const.\n    result_type query(int left, int right)\
    \ {\n        assert(0 <= left && left < right && right <= _n);\n\n        int\
    \ first_full = (left + _block_size - 1) / _block_size;\n        int last_full\
    \ = right / _block_size;\n        int left_end = std::min(right, block_start(first_full));\n\
    \        int right_start = std::max(left_end, block_start(last_full));\n\n   \
    \     int answer = -1;\n        int answer_frequency = 0;\n        if (first_full\
    \ < last_full) {\n            answer = _mode[first_full][last_full];\n       \
    \     answer_frequency = _mode_frequency[first_full][last_full];\n        }\n\n\
    \        _query_time++;\n        if (_query_time == 0) {\n            std::fill(_seen_at.begin(),\
    \ _seen_at.end(), 0);\n            _query_time = 1;\n        }\n        std::vector<int>\
    \ touched;\n        touched.reserve(left_end - left + right - right_start);\n\
    \        auto add = [&](int index) {\n            int value = _rank[index];\n\
    \            if (_seen_at[value] != _query_time) {\n                _seen_at[value]\
    \ = _query_time;\n                _extra_frequency[value] = 0;\n             \
    \   touched.push_back(value);\n            }\n            _extra_frequency[value]++;\n\
    \        };\n        for (int i = left; i < left_end; i++) add(i);\n        for\
    \ (int i = right_start; i < right; i++) add(i);\n\n        for (int value : touched)\
    \ {\n            int frequency = _extra_frequency[value];\n            if (first_full\
    \ < last_full) {\n                frequency +=\n                    _boundary_frequency[last_full][value]\n\
    \                    - _boundary_frequency[first_full][value];\n            }\n\
    \            if (frequency > answer_frequency) {\n                answer = value;\n\
    \                answer_frequency = frequency;\n            }\n        }\n   \
    \     assert(answer != -1);\n        return {_values[answer], answer_frequency};\n\
    \    }\n\n    result_type mode(int left, int right) {\n        return query(left,\
    \ right);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MODE_QUERY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/static_range_mode_query.hpp
  requiredBy: []
  timestamp: '2026-07-10 18:06:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/static_range_mode_query.test.cpp
documentation_of: ds/range_query/static_range_mode_query.hpp
layout: document
title: Static Range Mode Query
---

## Overview

`StaticRangeModeQuery<T>` preprocesses a static array and finds a mode of any
nonempty subarray `[left, right)`. A query returns the mode and its frequency.
If several values have maximum frequency, any one of them may be returned.

The array is divided into square-root-sized blocks. Modes of all complete-block
ranges and value frequencies at every block boundary are precomputed. Only the
two partial boundary blocks must be inspected during a query.

## Requirements

`T` must support `<` and equality consistently. The values are coordinate
compressed during construction. The input array is not modified.

## Complexity

| Operation | Time | Memory |
| --- | --- | --- |
| Construction | $O(N\sqrt N + N\log N)$ | $O(N\sqrt N)$ |
| Query | $O(\sqrt N)$ | $O(\sqrt N)$ temporary memory |

## Methods

| Method | Complexity | Description |
| --- | --- | --- |
| `StaticRangeModeQuery()` | $O(1)$ | Constructs an empty structure. |
| `explicit StaticRangeModeQuery(const std::vector<T>& values)` | $O(N\sqrt N + N\log N)$ | Builds the static structure. |
| `result_type query(int left, int right)` | $O(\sqrt N)$ | Returns `{mode, frequency}` for nonempty `[left, right)`. |
| `result_type mode(int left, int right)` | $O(\sqrt N)$ | Alias of `query`. |
| `int size() const` | $O(1)$ | Returns the array size. |
| `bool empty() const` | $O(1)$ | Returns whether the array is empty. |
| `int block_size() const` | $O(1)$ | Returns the selected block size. |

`result_type` is `std::pair<T, int>`. Queries reuse internal frequency
workspace, so `query` and `mode` are intentionally non-`const`. They do not
change the represented array or any future answer.

## Example

```cpp
#include "ds/range_query/static_range_mode_query.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {1, 2, 2, 3, 3, 3};
    m1une::ds::StaticRangeModeQuery<int> modes(values);

    auto answer = modes.query(1, 6);
    std::cout << answer.first << " " << answer.second << "\n"; // 3 3
}
```
