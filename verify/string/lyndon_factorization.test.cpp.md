---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/lyndon_factorization.hpp
    title: Lyndon Factorization
  - icon: ':heavy_check_mark:'
    path: string/minimum_rotation.hpp
    title: Minimum Rotation
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lyndon_factorization
    links:
    - https://judge.yosupo.jp/problem/lyndon_factorization
  bundledCode: "#line 1 \"verify/string/lyndon_factorization.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/lyndon_factorization\"\n\n#line 1 \"string/lyndon_factorization.hpp\"\
    \n\n\n\n#include <utility>\n#include <vector>\n\n#line 1 \"string/minimum_rotation.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace string {\n\n// Returns the smallest starting\
    \ index of a lexicographically minimum cyclic shift.\ntemplate <class Sequence>\n\
    int minimum_cyclic_shift(const Sequence& sequence) {\n    const int size = int(sequence.size());\n\
    \    if (size == 0) return 0;\n\n    auto less = [&](int left, int right) {\n\
    \        return sequence[left < size ? left : left - size] <\n               sequence[right\
    \ < size ? right : right - size];\n    };\n\n    int answer = 0;\n    int start\
    \ = 0;\n    while (start < size) {\n        answer = start;\n        int scan\
    \ = start + 1;\n        int matched = start;\n        while (scan < 2 * size &&\
    \ !less(scan, matched)) {\n            if (less(matched, scan)) {\n          \
    \      matched = start;\n            } else {\n                matched++;\n  \
    \          }\n            scan++;\n        }\n\n        const int period = scan\
    \ - matched;\n        while (start <= matched) start += period;\n    }\n    return\
    \ answer;\n}\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 8 \"\
    string/lyndon_factorization.hpp\"\n\nnamespace m1une {\nnamespace string {\n\n\
    // Returns boundaries 0 = a[0] < a[1] < ... < a[k] = sequence.size()\n// of the\
    \ Lyndon factorization.\ntemplate <class Sequence>\nstd::vector<int> lyndon_factor_boundaries(const\
    \ Sequence& sequence) {\n    int n = int(sequence.size());\n    std::vector<int>\
    \ boundaries;\n    boundaries.push_back(0);\n\n    int i = 0;\n    while (i <\
    \ n) {\n        int j = i + 1;\n        int k = i;\n        while (j < n && !(sequence[j]\
    \ < sequence[k])) {\n            if (sequence[k] < sequence[j]) {\n          \
    \      k = i;\n            } else {\n                k++;\n            }\n   \
    \         j++;\n        }\n\n        int length = j - k;\n        while (i <=\
    \ k) {\n            i += length;\n            boundaries.push_back(i);\n     \
    \   }\n    }\n    return boundaries;\n}\n\n// Returns half-open intervals [left,\
    \ right) of the Lyndon factorization.\ntemplate <class Sequence>\nstd::vector<std::pair<int,\
    \ int>> lyndon_factorization(const Sequence& sequence) {\n    std::vector<int>\
    \ boundaries = lyndon_factor_boundaries(sequence);\n    std::vector<std::pair<int,\
    \ int>> factors;\n    factors.reserve(boundaries.size() - 1);\n    for (int i\
    \ = 0; i + 1 < int(boundaries.size()); i++) {\n        factors.emplace_back(boundaries[i],\
    \ boundaries[i + 1]);\n    }\n    return factors;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 4 \"verify/string/lyndon_factorization.test.cpp\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <string>\n\
    #line 11 \"verify/string/lyndon_factorization.test.cpp\"\n\nnamespace {\n\nbool\
    \ is_strictly_smaller_rotation(const std::string& word, int offset) {\n    int\
    \ n = int(word.size());\n    for (int i = 0; i < n; i++) {\n        char a = word[i];\n\
    \        char b = word[(offset + i) % n];\n        if (a != b) return a < b;\n\
    \    }\n    return false;\n}\n\nbool is_lyndon_word(const std::string& word) {\n\
    \    if (word.empty()) return false;\n    for (int offset = 1; offset < int(word.size());\
    \ offset++) {\n        if (!is_strictly_smaller_rotation(word, offset)) return\
    \ false;\n    }\n    return true;\n}\n\nstd::vector<std::vector<int>> enumerate_factorizations(int\
    \ n) {\n    std::vector<std::vector<int>> result;\n    for (int mask = 0; mask\
    \ < (1 << (n - 1)); mask++) {\n        std::vector<int> boundaries;\n        boundaries.push_back(0);\n\
    \        for (int i = 1; i < n; i++) {\n            if ((mask >> (i - 1)) & 1)\
    \ boundaries.push_back(i);\n        }\n        boundaries.push_back(n);\n    \
    \    result.push_back(boundaries);\n    }\n    return result;\n}\n\nstd::vector<int>\
    \ naive_lyndon_factor_boundaries(const std::string& text) {\n    int n = int(text.size());\n\
    \    if (n == 0) return std::vector<int>(1, 0);\n\n    std::vector<int> best;\n\
    \    for (const std::vector<int>& boundaries : enumerate_factorizations(n)) {\n\
    \        bool valid = true;\n        std::vector<std::string> factors;\n     \
    \   for (int i = 0; i + 1 < int(boundaries.size()); i++) {\n            std::string\
    \ word =\n                text.substr(boundaries[i], boundaries[i + 1] - boundaries[i]);\n\
    \            if (!is_lyndon_word(word)) {\n                valid = false;\n  \
    \              break;\n            }\n            factors.push_back(word);\n \
    \       }\n        for (int i = 0; i + 1 < int(factors.size()); i++) {\n     \
    \       if (factors[i] < factors[i + 1]) {\n                valid = false;\n \
    \               break;\n            }\n        }\n        if (valid) {\n     \
    \       assert(best.empty());\n            best = boundaries;\n        }\n   \
    \ }\n    assert(!best.empty());\n    return best;\n}\n\nstd::string cyclic_shift(const\
    \ std::string& text, int start) {\n    return text.substr(start) + text.substr(0,\
    \ start);\n}\n\nint naive_minimum_cyclic_shift(const std::string& text) {\n  \
    \  int n = int(text.size());\n    if (n == 0) return 0;\n\n    int best = 0;\n\
    \    for (int start = 1; start < n; start++) {\n        if (cyclic_shift(text,\
    \ start) < cyclic_shift(text, best)) {\n            best = start;\n        }\n\
    \    }\n    return best;\n}\n\nvoid test_edge_cases() {\n    std::string empty;\n\
    \    assert(m1une::string::lyndon_factor_boundaries(empty) == std::vector<int>(1,\
    \ 0));\n    assert(m1une::string::lyndon_factorization(empty).empty());\n    assert(m1une::string::minimum_cyclic_shift(empty)\
    \ == 0);\n\n    assert(\n        m1une::string::lyndon_factor_boundaries(std::string(\"\
    aaaa\")) ==\n        std::vector<int>({0, 1, 2, 3, 4})\n    );\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    aaaa\")) == 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    abab\")) == 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    banana\")) == 5);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    baca\")) == 3);\n\n    std::vector<std::pair<int, int>> expected;\n    expected.emplace_back(0,\
    \ 1);\n    expected.emplace_back(1, 3);\n    expected.emplace_back(3, 4);\n  \
    \  assert(m1une::string::lyndon_factorization(std::string(\"baca\")) == expected);\n\
    \n    std::vector<int> values;\n    values.push_back(2);\n    values.push_back(1);\n\
    \    values.push_back(3);\n    values.push_back(1);\n    assert(\n        m1une::string::lyndon_factor_boundaries(values)\
    \ ==\n        std::vector<int>({0, 1, 3, 4})\n    );\n    assert(m1une::string::minimum_cyclic_shift(values)\
    \ == 3);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 20260709;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 1200; trial++) {\n        int n = int(random() % 10);\n        std::string\
    \ text(n, 'a');\n        for (char& character : text) character = char('a' + random()\
    \ % 4);\n\n        std::vector<int> boundaries = m1une::string::lyndon_factor_boundaries(text);\n\
    \        std::vector<int> expected = naive_lyndon_factor_boundaries(text);\n \
    \       assert(boundaries == expected);\n        assert(\n            m1une::string::minimum_cyclic_shift(text)\
    \ ==\n            naive_minimum_cyclic_shift(text)\n        );\n\n        std::vector<std::pair<int,\
    \ int>> factors = m1une::string::lyndon_factorization(text);\n        assert(int(factors.size())\
    \ + 1 == int(boundaries.size()));\n        for (int i = 0; i < int(factors.size());\
    \ i++) {\n            assert(factors[i].first == boundaries[i]);\n           \
    \ assert(factors[i].second == boundaries[i + 1]);\n        }\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    test_edge_cases();\n    test_randomized();\n\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    std::string\
    \ text;\n    std::cin >> text;\n    std::vector<int> boundaries = m1une::string::lyndon_factor_boundaries(text);\n\
    \    for (int i = 0; i < int(boundaries.size()); i++) {\n        if (i > 0) std::cout\
    \ << ' ';\n        std::cout << boundaries[i];\n    }\n    std::cout << '\\n';\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lyndon_factorization\"\n\
    \n#include \"../../string/lyndon_factorization.hpp\"\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <iostream>\n#include <string>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace {\n\nbool is_strictly_smaller_rotation(const std::string&\
    \ word, int offset) {\n    int n = int(word.size());\n    for (int i = 0; i <\
    \ n; i++) {\n        char a = word[i];\n        char b = word[(offset + i) % n];\n\
    \        if (a != b) return a < b;\n    }\n    return false;\n}\n\nbool is_lyndon_word(const\
    \ std::string& word) {\n    if (word.empty()) return false;\n    for (int offset\
    \ = 1; offset < int(word.size()); offset++) {\n        if (!is_strictly_smaller_rotation(word,\
    \ offset)) return false;\n    }\n    return true;\n}\n\nstd::vector<std::vector<int>>\
    \ enumerate_factorizations(int n) {\n    std::vector<std::vector<int>> result;\n\
    \    for (int mask = 0; mask < (1 << (n - 1)); mask++) {\n        std::vector<int>\
    \ boundaries;\n        boundaries.push_back(0);\n        for (int i = 1; i < n;\
    \ i++) {\n            if ((mask >> (i - 1)) & 1) boundaries.push_back(i);\n  \
    \      }\n        boundaries.push_back(n);\n        result.push_back(boundaries);\n\
    \    }\n    return result;\n}\n\nstd::vector<int> naive_lyndon_factor_boundaries(const\
    \ std::string& text) {\n    int n = int(text.size());\n    if (n == 0) return\
    \ std::vector<int>(1, 0);\n\n    std::vector<int> best;\n    for (const std::vector<int>&\
    \ boundaries : enumerate_factorizations(n)) {\n        bool valid = true;\n  \
    \      std::vector<std::string> factors;\n        for (int i = 0; i + 1 < int(boundaries.size());\
    \ i++) {\n            std::string word =\n                text.substr(boundaries[i],\
    \ boundaries[i + 1] - boundaries[i]);\n            if (!is_lyndon_word(word))\
    \ {\n                valid = false;\n                break;\n            }\n \
    \           factors.push_back(word);\n        }\n        for (int i = 0; i + 1\
    \ < int(factors.size()); i++) {\n            if (factors[i] < factors[i + 1])\
    \ {\n                valid = false;\n                break;\n            }\n \
    \       }\n        if (valid) {\n            assert(best.empty());\n         \
    \   best = boundaries;\n        }\n    }\n    assert(!best.empty());\n    return\
    \ best;\n}\n\nstd::string cyclic_shift(const std::string& text, int start) {\n\
    \    return text.substr(start) + text.substr(0, start);\n}\n\nint naive_minimum_cyclic_shift(const\
    \ std::string& text) {\n    int n = int(text.size());\n    if (n == 0) return\
    \ 0;\n\n    int best = 0;\n    for (int start = 1; start < n; start++) {\n   \
    \     if (cyclic_shift(text, start) < cyclic_shift(text, best)) {\n          \
    \  best = start;\n        }\n    }\n    return best;\n}\n\nvoid test_edge_cases()\
    \ {\n    std::string empty;\n    assert(m1une::string::lyndon_factor_boundaries(empty)\
    \ == std::vector<int>(1, 0));\n    assert(m1une::string::lyndon_factorization(empty).empty());\n\
    \    assert(m1une::string::minimum_cyclic_shift(empty) == 0);\n\n    assert(\n\
    \        m1une::string::lyndon_factor_boundaries(std::string(\"aaaa\")) ==\n \
    \       std::vector<int>({0, 1, 2, 3, 4})\n    );\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    aaaa\")) == 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    abab\")) == 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    banana\")) == 5);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    baca\")) == 3);\n\n    std::vector<std::pair<int, int>> expected;\n    expected.emplace_back(0,\
    \ 1);\n    expected.emplace_back(1, 3);\n    expected.emplace_back(3, 4);\n  \
    \  assert(m1une::string::lyndon_factorization(std::string(\"baca\")) == expected);\n\
    \n    std::vector<int> values;\n    values.push_back(2);\n    values.push_back(1);\n\
    \    values.push_back(3);\n    values.push_back(1);\n    assert(\n        m1une::string::lyndon_factor_boundaries(values)\
    \ ==\n        std::vector<int>({0, 1, 3, 4})\n    );\n    assert(m1une::string::minimum_cyclic_shift(values)\
    \ == 3);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 20260709;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 1200; trial++) {\n        int n = int(random() % 10);\n        std::string\
    \ text(n, 'a');\n        for (char& character : text) character = char('a' + random()\
    \ % 4);\n\n        std::vector<int> boundaries = m1une::string::lyndon_factor_boundaries(text);\n\
    \        std::vector<int> expected = naive_lyndon_factor_boundaries(text);\n \
    \       assert(boundaries == expected);\n        assert(\n            m1une::string::minimum_cyclic_shift(text)\
    \ ==\n            naive_minimum_cyclic_shift(text)\n        );\n\n        std::vector<std::pair<int,\
    \ int>> factors = m1une::string::lyndon_factorization(text);\n        assert(int(factors.size())\
    \ + 1 == int(boundaries.size()));\n        for (int i = 0; i < int(factors.size());\
    \ i++) {\n            assert(factors[i].first == boundaries[i]);\n           \
    \ assert(factors[i].second == boundaries[i + 1]);\n        }\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    test_edge_cases();\n    test_randomized();\n\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    std::string\
    \ text;\n    std::cin >> text;\n    std::vector<int> boundaries = m1une::string::lyndon_factor_boundaries(text);\n\
    \    for (int i = 0; i < int(boundaries.size()); i++) {\n        if (i > 0) std::cout\
    \ << ' ';\n        std::cout << boundaries[i];\n    }\n    std::cout << '\\n';\n\
    }\n"
  dependsOn:
  - string/lyndon_factorization.hpp
  - string/minimum_rotation.hpp
  isVerificationFile: true
  path: verify/string/lyndon_factorization.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 05:39:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/lyndon_factorization.test.cpp
layout: document
redirect_from:
- /verify/verify/string/lyndon_factorization.test.cpp
- /verify/verify/string/lyndon_factorization.test.cpp.html
title: verify/string/lyndon_factorization.test.cpp
---
