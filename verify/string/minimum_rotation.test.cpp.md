---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: string/minimum_rotation.hpp
    title: Minimum Rotation
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/string/minimum_rotation.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"string/minimum_rotation.hpp\"\
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
    \ answer;\n}\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 4 \"\
    verify/string/minimum_rotation.test.cpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <string>\n#include <vector>\n\nnamespace {\n\ntemplate\
    \ <class Sequence>\nbool rotation_less(\n    const Sequence& sequence,\n    int\
    \ first,\n    int second\n) {\n    const int size = int(sequence.size());\n  \
    \  for (int offset = 0; offset < size; offset++) {\n        const auto& left =\
    \ sequence[(first + offset) % size];\n        const auto& right = sequence[(second\
    \ + offset) % size];\n        if (left < right) return true;\n        if (right\
    \ < left) return false;\n    }\n    return false;\n}\n\ntemplate <class Sequence>\n\
    int naive_minimum_cyclic_shift(const Sequence& sequence) {\n    if (sequence.empty())\
    \ return 0;\n    int answer = 0;\n    for (int start = 1; start < int(sequence.size());\
    \ start++) {\n        if (rotation_less(sequence, start, answer)) answer = start;\n\
    \    }\n    return answer;\n}\n\nvoid test_edge_cases() {\n    assert(m1une::string::minimum_cyclic_shift(std::string())\
    \ == 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"a\")) ==\
    \ 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"aaaa\")) ==\
    \ 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"abab\")) ==\
    \ 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"banana\"))\
    \ == 5);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"baca\"\
    )) == 3);\n\n    std::vector<int> values{2, 1, 3, 1};\n    assert(m1une::string::minimum_cyclic_shift(values)\
    \ == 3);\n}\n\nvoid test_exhaustive() {\n    for (int size = 0; size <= 9; size++)\
    \ {\n        std::uint64_t count = 1;\n        for (int index = 0; index < size;\
    \ index++) count *= 3;\n        for (std::uint64_t code = 0; code < count; code++)\
    \ {\n            std::uint64_t value = code;\n            std::string text(static_cast<std::size_t>(size),\
    \ 'a');\n            for (char& character : text) {\n                character\
    \ = char('a' + value % 3);\n                value /= 3;\n            }\n     \
    \       assert(\n                m1une::string::minimum_cyclic_shift(text) ==\n\
    \                naive_minimum_cyclic_shift(text)\n            );\n        }\n\
    \    }\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0x816f3ac924b75de0ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 5000; trial++) {\n        const int size = int(random() % 50);\n        std::vector<int>\
    \ sequence(static_cast<std::size_t>(size));\n        for (int& value : sequence)\
    \ value = int(random() % 7);\n        assert(\n            m1une::string::minimum_cyclic_shift(sequence)\
    \ ==\n            naive_minimum_cyclic_shift(sequence)\n        );\n    }\n}\n\
    \n}  // namespace\n\nint main() {\n    test_edge_cases();\n    test_exhaustive();\n\
    \    test_randomized();\n\n    long long first, second;\n    std::cin >> first\
    \ >> second;\n    std::cout << first + second << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../string/minimum_rotation.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <string>\n#include <vector>\n\nnamespace {\n\ntemplate\
    \ <class Sequence>\nbool rotation_less(\n    const Sequence& sequence,\n    int\
    \ first,\n    int second\n) {\n    const int size = int(sequence.size());\n  \
    \  for (int offset = 0; offset < size; offset++) {\n        const auto& left =\
    \ sequence[(first + offset) % size];\n        const auto& right = sequence[(second\
    \ + offset) % size];\n        if (left < right) return true;\n        if (right\
    \ < left) return false;\n    }\n    return false;\n}\n\ntemplate <class Sequence>\n\
    int naive_minimum_cyclic_shift(const Sequence& sequence) {\n    if (sequence.empty())\
    \ return 0;\n    int answer = 0;\n    for (int start = 1; start < int(sequence.size());\
    \ start++) {\n        if (rotation_less(sequence, start, answer)) answer = start;\n\
    \    }\n    return answer;\n}\n\nvoid test_edge_cases() {\n    assert(m1une::string::minimum_cyclic_shift(std::string())\
    \ == 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"a\")) ==\
    \ 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"aaaa\")) ==\
    \ 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"abab\")) ==\
    \ 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"banana\"))\
    \ == 5);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"baca\"\
    )) == 3);\n\n    std::vector<int> values{2, 1, 3, 1};\n    assert(m1une::string::minimum_cyclic_shift(values)\
    \ == 3);\n}\n\nvoid test_exhaustive() {\n    for (int size = 0; size <= 9; size++)\
    \ {\n        std::uint64_t count = 1;\n        for (int index = 0; index < size;\
    \ index++) count *= 3;\n        for (std::uint64_t code = 0; code < count; code++)\
    \ {\n            std::uint64_t value = code;\n            std::string text(static_cast<std::size_t>(size),\
    \ 'a');\n            for (char& character : text) {\n                character\
    \ = char('a' + value % 3);\n                value /= 3;\n            }\n     \
    \       assert(\n                m1une::string::minimum_cyclic_shift(text) ==\n\
    \                naive_minimum_cyclic_shift(text)\n            );\n        }\n\
    \    }\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0x816f3ac924b75de0ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 5000; trial++) {\n        const int size = int(random() % 50);\n        std::vector<int>\
    \ sequence(static_cast<std::size_t>(size));\n        for (int& value : sequence)\
    \ value = int(random() % 7);\n        assert(\n            m1une::string::minimum_cyclic_shift(sequence)\
    \ ==\n            naive_minimum_cyclic_shift(sequence)\n        );\n    }\n}\n\
    \n}  // namespace\n\nint main() {\n    test_edge_cases();\n    test_exhaustive();\n\
    \    test_randomized();\n\n    long long first, second;\n    std::cin >> first\
    \ >> second;\n    std::cout << first + second << '\\n';\n}\n"
  dependsOn:
  - string/minimum_rotation.hpp
  isVerificationFile: true
  path: verify/string/minimum_rotation.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 05:39:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/minimum_rotation.test.cpp
layout: document
redirect_from:
- /verify/verify/string/minimum_rotation.test.cpp
- /verify/verify/string/minimum_rotation.test.cpp.html
title: verify/string/minimum_rotation.test.cpp
---
