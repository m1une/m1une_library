---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/runs.test.cpp
    title: verify/string/runs.test.cpp
  - icon: ':x:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/runs.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <set>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ string {\n\nstruct Run {\n    int period;\n    int left;\n    int right;\n\n\
    \    bool operator==(const Run&) const = default;\n};\n\nnamespace internal {\n\
    \ntemplate <class Sequence>\nclass RunEnumerator {\n   private:\n    const Sequence&\
    \ _sequence;\n    int _size;\n    std::vector<std::vector<std::pair<int, int>>>\
    \ _candidates;\n\n    template <class Access>\n    static std::vector<int> z_algorithm(int\
    \ length, Access access) {\n        std::vector<int> z(length + 1, 0);\n     \
    \   if (length == 0) return z;\n        z[0] = length;\n        int left = 0;\n\
    \        int right = 0;\n        for (int i = 1; i < length; i++) {\n        \
    \    if (i < right) z[i] = std::min(right - i, z[i - left]);\n            while\
    \ (\n                i + z[i] < length &&\n                access(z[i]) == access(i\
    \ + z[i])\n            ) {\n                z[i]++;\n            }\n         \
    \   if (right < i + z[i]) {\n                left = i;\n                right\
    \ = i + z[i];\n            }\n        }\n        return z;\n    }\n\n    decltype(auto)\
    \ element(int index, bool reversed) const {\n        int original_index = reversed\
    \ ? _size - 1 - index : index;\n        return _sequence[original_index];\n  \
    \  }\n\n    void add_candidate(int period, int left, int right, bool reversed)\
    \ {\n        if (reversed) {\n            left = _size - left;\n            right\
    \ = _size - right;\n            std::swap(left, right);\n        }\n        _candidates[period].emplace_back(left,\
    \ right);\n    }\n\n    void collect(int range_left, int range_right, int phase,\
    \ bool reversed) {\n        if (range_right - range_left <= 1) return;\n     \
    \   int middle = (range_left + range_right + phase) / 2;\n        collect(range_left,\
    \ middle, phase, reversed);\n        collect(middle, range_right, phase, reversed);\n\
    \n        int left_length = middle - range_left;\n        int right_length = range_right\
    \ - middle;\n        std::vector<int> left_z = z_algorithm(left_length, [&](int\
    \ index) -> decltype(auto) {\n            return element(middle - 1 - index, reversed);\n\
    \        });\n\n        int combined_length = right_length + range_right - range_left;\n\
    \        std::vector<int> right_z = z_algorithm(combined_length, [&](int index)\
    \ -> decltype(auto) {\n            if (index < right_length) return element(middle\
    \ + index, reversed);\n            return element(range_left + index - right_length,\
    \ reversed);\n        });\n\n        for (int start = middle - 1; start >= range_left;\
    \ start--) {\n            int period = middle - start;\n            int extend_left\
    \ = std::min(start - range_left, left_z[period]);\n            int extend_right\
    \ = std::min(\n                range_right - middle,\n                right_z[range_right\
    \ - range_left - period]\n            );\n            int left = start - extend_left;\n\
    \            int right = middle + extend_right;\n            if (right - left\
    \ >= 2 * period) {\n                add_candidate(period, left, right, reversed);\n\
    \            }\n        }\n    }\n\n   public:\n    explicit RunEnumerator(const\
    \ Sequence& sequence)\n        : _sequence(sequence),\n          _size(int(sequence.size())),\n\
    \          _candidates(_size / 2 + 1) {}\n\n    std::vector<Run> enumerate() {\n\
    \        collect(0, _size, 0, true);\n        collect(0, _size, 1, false);\n\n\
    \        std::set<std::pair<int, int>> used_intervals;\n        std::vector<Run>\
    \ result;\n        for (int period = 1; period <= _size / 2; period++) {\n   \
    \         std::vector<std::pair<int, int>>& candidates = _candidates[period];\n\
    \            std::sort(\n                candidates.begin(),\n               \
    \ candidates.end(),\n                [](const auto& first, const auto& second)\
    \ {\n                    if (first.first != second.first) {\n                \
    \        return first.first < second.first;\n                    }\n         \
    \           return first.second > second.second;\n                }\n        \
    \    );\n\n            int farthest_right = -1;\n            for (const auto&\
    \ interval : candidates) {\n                if (interval.second <= farthest_right)\
    \ continue;\n                farthest_right = interval.second;\n             \
    \   if (!used_intervals.insert(interval).second) continue;\n                result.push_back(Run{period,\
    \ interval.first, interval.second});\n            }\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace internal\n\n// Returns all runs as (minimum\
    \ period, maximal half-open interval),\n// sorted lexicographically by (period,\
    \ left, right).\ntemplate <class Sequence>\nstd::vector<Run> enumerate_runs(const\
    \ Sequence& sequence) {\n    return internal::RunEnumerator<Sequence>(sequence).enumerate();\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_RUNS_HPP\n#define M1UNE_STRING_RUNS_HPP 1\n\n#include\
    \ <algorithm>\n#include <set>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace string {\n\nstruct Run {\n    int period;\n    int left;\n\
    \    int right;\n\n    bool operator==(const Run&) const = default;\n};\n\nnamespace\
    \ internal {\n\ntemplate <class Sequence>\nclass RunEnumerator {\n   private:\n\
    \    const Sequence& _sequence;\n    int _size;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _candidates;\n\n    template <class Access>\n    static std::vector<int>\
    \ z_algorithm(int length, Access access) {\n        std::vector<int> z(length\
    \ + 1, 0);\n        if (length == 0) return z;\n        z[0] = length;\n     \
    \   int left = 0;\n        int right = 0;\n        for (int i = 1; i < length;\
    \ i++) {\n            if (i < right) z[i] = std::min(right - i, z[i - left]);\n\
    \            while (\n                i + z[i] < length &&\n                access(z[i])\
    \ == access(i + z[i])\n            ) {\n                z[i]++;\n            }\n\
    \            if (right < i + z[i]) {\n                left = i;\n            \
    \    right = i + z[i];\n            }\n        }\n        return z;\n    }\n\n\
    \    decltype(auto) element(int index, bool reversed) const {\n        int original_index\
    \ = reversed ? _size - 1 - index : index;\n        return _sequence[original_index];\n\
    \    }\n\n    void add_candidate(int period, int left, int right, bool reversed)\
    \ {\n        if (reversed) {\n            left = _size - left;\n            right\
    \ = _size - right;\n            std::swap(left, right);\n        }\n        _candidates[period].emplace_back(left,\
    \ right);\n    }\n\n    void collect(int range_left, int range_right, int phase,\
    \ bool reversed) {\n        if (range_right - range_left <= 1) return;\n     \
    \   int middle = (range_left + range_right + phase) / 2;\n        collect(range_left,\
    \ middle, phase, reversed);\n        collect(middle, range_right, phase, reversed);\n\
    \n        int left_length = middle - range_left;\n        int right_length = range_right\
    \ - middle;\n        std::vector<int> left_z = z_algorithm(left_length, [&](int\
    \ index) -> decltype(auto) {\n            return element(middle - 1 - index, reversed);\n\
    \        });\n\n        int combined_length = right_length + range_right - range_left;\n\
    \        std::vector<int> right_z = z_algorithm(combined_length, [&](int index)\
    \ -> decltype(auto) {\n            if (index < right_length) return element(middle\
    \ + index, reversed);\n            return element(range_left + index - right_length,\
    \ reversed);\n        });\n\n        for (int start = middle - 1; start >= range_left;\
    \ start--) {\n            int period = middle - start;\n            int extend_left\
    \ = std::min(start - range_left, left_z[period]);\n            int extend_right\
    \ = std::min(\n                range_right - middle,\n                right_z[range_right\
    \ - range_left - period]\n            );\n            int left = start - extend_left;\n\
    \            int right = middle + extend_right;\n            if (right - left\
    \ >= 2 * period) {\n                add_candidate(period, left, right, reversed);\n\
    \            }\n        }\n    }\n\n   public:\n    explicit RunEnumerator(const\
    \ Sequence& sequence)\n        : _sequence(sequence),\n          _size(int(sequence.size())),\n\
    \          _candidates(_size / 2 + 1) {}\n\n    std::vector<Run> enumerate() {\n\
    \        collect(0, _size, 0, true);\n        collect(0, _size, 1, false);\n\n\
    \        std::set<std::pair<int, int>> used_intervals;\n        std::vector<Run>\
    \ result;\n        for (int period = 1; period <= _size / 2; period++) {\n   \
    \         std::vector<std::pair<int, int>>& candidates = _candidates[period];\n\
    \            std::sort(\n                candidates.begin(),\n               \
    \ candidates.end(),\n                [](const auto& first, const auto& second)\
    \ {\n                    if (first.first != second.first) {\n                \
    \        return first.first < second.first;\n                    }\n         \
    \           return first.second > second.second;\n                }\n        \
    \    );\n\n            int farthest_right = -1;\n            for (const auto&\
    \ interval : candidates) {\n                if (interval.second <= farthest_right)\
    \ continue;\n                farthest_right = interval.second;\n             \
    \   if (!used_intervals.insert(interval).second) continue;\n                result.push_back(Run{period,\
    \ interval.first, interval.second});\n            }\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace internal\n\n// Returns all runs as (minimum\
    \ period, maximal half-open interval),\n// sorted lexicographically by (period,\
    \ left, right).\ntemplate <class Sequence>\nstd::vector<Run> enumerate_runs(const\
    \ Sequence& sequence) {\n    return internal::RunEnumerator<Sequence>(sequence).enumerate();\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_RUNS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/runs.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-13 04:16:09+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/runs.test.cpp
documentation_of: string/runs.hpp
layout: document
title: Runs
---

## Overview

A run is a maximal periodic substring whose length is at least twice its
minimum period. This header enumerates every run of an indexable sequence.
It uses zero-based indices and represents substrings as half-open intervals.

The sequence elements only need to support equality comparison. Strings and
vectors of integers can be passed directly.

## Interface

| Interface | Description | Complexity |
| --- | --- | --- |
| `Run` | A result with fields `int period`, `int left`, and `int right`. | -- |
| `vector<Run> enumerate_runs(const Sequence& sequence)` | Returns all runs in lexicographic `(period, left, right)` order. | $O(N \log N)$ time and $O(N \log N)$ memory |

For each returned run, `[left, right)` has minimum period `period`, its length
is at least `2 * period`, and it cannot be extended one position to either side
while preserving that period. The empty sequence has no runs.

## Example

```cpp
#include "string/runs.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "mississippi";
    for (const auto& run : m1une::string::enumerate_runs(text)) {
        std::cout << run.period << ' ' << run.left << ' ' << run.right << '\n';
    }
}
```
