---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/runs.hpp
    title: Runs
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/runenumerate
    links:
    - https://judge.yosupo.jp/problem/runenumerate
  bundledCode: "#line 1 \"verify/string/runs.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\
    \n\n#line 1 \"string/runs.hpp\"\n\n\n\n#include <algorithm>\n#include <set>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\
    \nstruct Run {\n    int period;\n    int left;\n    int right;\n\n    bool operator==(const\
    \ Run&) const = default;\n};\n\nnamespace internal {\n\ntemplate <class Sequence>\n\
    class RunEnumerator {\n   private:\n    const Sequence& _sequence;\n    int _size;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _candidates;\n\n    template\
    \ <class Access>\n    static std::vector<int> z_algorithm(int length, Access access)\
    \ {\n        std::vector<int> z(length + 1, 0);\n        if (length == 0) return\
    \ z;\n        z[0] = length;\n        int left = 0;\n        int right = 0;\n\
    \        for (int i = 1; i < length; i++) {\n            if (i < right) z[i] =\
    \ std::min(right - i, z[i - left]);\n            while (\n                i +\
    \ z[i] < length &&\n                access(z[i]) == access(i + z[i])\n       \
    \     ) {\n                z[i]++;\n            }\n            if (right < i +\
    \ z[i]) {\n                left = i;\n                right = i + z[i];\n    \
    \        }\n        }\n        return z;\n    }\n\n    decltype(auto) element(int\
    \ index, bool reversed) const {\n        int original_index = reversed ? _size\
    \ - 1 - index : index;\n        return _sequence[original_index];\n    }\n\n \
    \   void add_candidate(int period, int left, int right, bool reversed) {\n   \
    \     if (reversed) {\n            left = _size - left;\n            right = _size\
    \ - right;\n            std::swap(left, right);\n        }\n        _candidates[period].emplace_back(left,\
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
    }\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/runs.test.cpp\"\
    \n\n#line 6 \"verify/string/runs.test.cpp\"\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <string>\n#line 11 \"verify/string/runs.test.cpp\"\
    \n\nnamespace {\n\nbool has_period(const std::string& text, int left, int right,\
    \ int period) {\n    for (int i = left; i + period < right; i++) {\n        if\
    \ (text[i] != text[i + period]) return false;\n    }\n    return true;\n}\n\n\
    std::vector<m1une::string::Run> naive_runs(const std::string& text) {\n    int\
    \ n = int(text.size());\n    std::vector<m1une::string::Run> result;\n    for\
    \ (int left = 0; left < n; left++) {\n        for (int right = left + 2; right\
    \ <= n; right++) {\n            int minimum_period = right - left;\n         \
    \   for (int period = 1; period < right - left; period++) {\n                if\
    \ (has_period(text, left, right, period)) {\n                    minimum_period\
    \ = period;\n                    break;\n                }\n            }\n  \
    \          if (right - left < 2 * minimum_period) continue;\n            if (\n\
    \                left > 0 &&\n                text[left - 1] == text[left - 1\
    \ + minimum_period]\n            ) {\n                continue;\n            }\n\
    \            if (\n                right < n &&\n                text[right] ==\
    \ text[right - minimum_period]\n            ) {\n                continue;\n \
    \           }\n            result.push_back(m1une::string::Run{minimum_period,\
    \ left, right});\n        }\n    }\n    std::sort(result.begin(), result.end(),\
    \ [](const auto& first, const auto& second) {\n        if (first.period != second.period)\
    \ return first.period < second.period;\n        if (first.left != second.left)\
    \ return first.left < second.left;\n        return first.right < second.right;\n\
    \    });\n    return result;\n}\n\nvoid test_edge_cases() {\n    std::string empty;\n\
    \    assert(m1une::string::enumerate_runs(empty).empty());\n    assert(m1une::string::enumerate_runs(std::string(\"\
    a\")).empty());\n\n    std::vector<m1une::string::Run> equal_expected;\n    equal_expected.push_back(m1une::string::Run{1,\
    \ 0, 5});\n    assert(m1une::string::enumerate_runs(std::string(\"aaaaa\")) ==\
    \ equal_expected);\n\n    std::vector<int> values;\n    values.push_back(4);\n\
    \    values.push_back(7);\n    values.push_back(4);\n    values.push_back(7);\n\
    \    values.push_back(4);\n    std::vector<m1une::string::Run> vector_expected;\n\
    \    vector_expected.push_back(m1une::string::Run{2, 0, 5});\n    assert(m1une::string::enumerate_runs(values)\
    \ == vector_expected);\n\n    std::vector<bool> bits(6, false);\n    bits[1] =\
    \ true;\n    bits[3] = true;\n    bits[5] = true;\n    std::vector<m1une::string::Run>\
    \ bit_expected;\n    bit_expected.push_back(m1une::string::Run{2, 0, 6});\n  \
    \  assert(m1une::string::enumerate_runs(bits) == bit_expected);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20260713;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 5000; trial++) {\n        int n = int(random()\
    \ % 14);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 4);\n        assert(m1une::string::enumerate_runs(text)\
    \ == naive_runs(text));\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_edge_cases();\n\
    \    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::string text;\n    std::cin >> text;\n    std::vector<m1une::string::Run>\
    \ runs = m1une::string::enumerate_runs(text);\n    std::cout << runs.size() <<\
    \ '\\n';\n    for (const auto& run : runs) {\n        std::cout << run.period\
    \ << ' ' << run.left << ' ' << run.right << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\n\n#include\
    \ \"../../string/runs.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cstdint>\n#include <iostream>\n#include <string>\n#include <vector>\n\nnamespace\
    \ {\n\nbool has_period(const std::string& text, int left, int right, int period)\
    \ {\n    for (int i = left; i + period < right; i++) {\n        if (text[i] !=\
    \ text[i + period]) return false;\n    }\n    return true;\n}\n\nstd::vector<m1une::string::Run>\
    \ naive_runs(const std::string& text) {\n    int n = int(text.size());\n    std::vector<m1une::string::Run>\
    \ result;\n    for (int left = 0; left < n; left++) {\n        for (int right\
    \ = left + 2; right <= n; right++) {\n            int minimum_period = right -\
    \ left;\n            for (int period = 1; period < right - left; period++) {\n\
    \                if (has_period(text, left, right, period)) {\n              \
    \      minimum_period = period;\n                    break;\n                }\n\
    \            }\n            if (right - left < 2 * minimum_period) continue;\n\
    \            if (\n                left > 0 &&\n                text[left - 1]\
    \ == text[left - 1 + minimum_period]\n            ) {\n                continue;\n\
    \            }\n            if (\n                right < n &&\n             \
    \   text[right] == text[right - minimum_period]\n            ) {\n           \
    \     continue;\n            }\n            result.push_back(m1une::string::Run{minimum_period,\
    \ left, right});\n        }\n    }\n    std::sort(result.begin(), result.end(),\
    \ [](const auto& first, const auto& second) {\n        if (first.period != second.period)\
    \ return first.period < second.period;\n        if (first.left != second.left)\
    \ return first.left < second.left;\n        return first.right < second.right;\n\
    \    });\n    return result;\n}\n\nvoid test_edge_cases() {\n    std::string empty;\n\
    \    assert(m1une::string::enumerate_runs(empty).empty());\n    assert(m1une::string::enumerate_runs(std::string(\"\
    a\")).empty());\n\n    std::vector<m1une::string::Run> equal_expected;\n    equal_expected.push_back(m1une::string::Run{1,\
    \ 0, 5});\n    assert(m1une::string::enumerate_runs(std::string(\"aaaaa\")) ==\
    \ equal_expected);\n\n    std::vector<int> values;\n    values.push_back(4);\n\
    \    values.push_back(7);\n    values.push_back(4);\n    values.push_back(7);\n\
    \    values.push_back(4);\n    std::vector<m1une::string::Run> vector_expected;\n\
    \    vector_expected.push_back(m1une::string::Run{2, 0, 5});\n    assert(m1une::string::enumerate_runs(values)\
    \ == vector_expected);\n\n    std::vector<bool> bits(6, false);\n    bits[1] =\
    \ true;\n    bits[3] = true;\n    bits[5] = true;\n    std::vector<m1une::string::Run>\
    \ bit_expected;\n    bit_expected.push_back(m1une::string::Run{2, 0, 6});\n  \
    \  assert(m1une::string::enumerate_runs(bits) == bit_expected);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20260713;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 5000; trial++) {\n        int n = int(random()\
    \ % 14);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 4);\n        assert(m1une::string::enumerate_runs(text)\
    \ == naive_runs(text));\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_edge_cases();\n\
    \    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::string text;\n    std::cin >> text;\n    std::vector<m1une::string::Run>\
    \ runs = m1une::string::enumerate_runs(text);\n    std::cout << runs.size() <<\
    \ '\\n';\n    for (const auto& run : runs) {\n        std::cout << run.period\
    \ << ' ' << run.left << ' ' << run.right << '\\n';\n    }\n}\n"
  dependsOn:
  - string/runs.hpp
  isVerificationFile: true
  path: verify/string/runs.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 04:16:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/runs.test.cpp
layout: document
redirect_from:
- /verify/verify/string/runs.test.cpp
- /verify/verify/string/runs.test.cpp.html
title: verify/string/runs.test.cpp
---
