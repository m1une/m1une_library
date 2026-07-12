---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick.hpp
    title: Aho-Corasick
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  - icon: ':heavy_check_mark:'
    path: string/eertree.hpp
    title: Eertree
  - icon: ':heavy_check_mark:'
    path: string/levenshtein_distance.hpp
    title: Levenshtein Distance
  - icon: ':heavy_check_mark:'
    path: string/longest_common_extension.hpp
    title: Longest Common Extension
  - icon: ':heavy_check_mark:'
    path: string/longest_common_subsequence.hpp
    title: Longest Common Subsequence
  - icon: ':heavy_check_mark:'
    path: string/longest_common_substring.hpp
    title: Longest Common Substring
  - icon: ':heavy_check_mark:'
    path: string/lyndon_factorization.hpp
    title: Lyndon Factorization
  - icon: ':heavy_check_mark:'
    path: string/manacher.hpp
    title: Manacher Algorithm
  - icon: ':heavy_check_mark:'
    path: string/prefix_function.hpp
    title: Prefix Function and KMP
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: Static Rolling Hash
  - icon: ':heavy_check_mark:'
    path: string/runs.hpp
    title: Runs
  - icon: ':heavy_check_mark:'
    path: string/string_hash.hpp
    title: String Hash
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.hpp
    title: Suffix Array and LCP Array
  - icon: ':heavy_check_mark:'
    path: string/suffix_automaton.hpp
    title: Suffix Automaton
  - icon: ':heavy_check_mark:'
    path: string/trie.hpp
    title: Trie
  - icon: ':heavy_check_mark:'
    path: string/wildcard_pattern_matching.hpp
    title: Wildcard Pattern Matching
  - icon: ':heavy_check_mark:'
    path: string/z_algorithm.hpp
    title: Z Algorithm
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
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../string/all.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <numeric>\n#include <string>\n#include <vector>\n\
    \nnamespace {\n\nvoid test_edge_cases() {\n    std::string empty;\n    assert(m1une::string::z_algorithm(empty).empty());\n\
    \    assert(m1une::string::prefix_function(empty).empty());\n    assert(m1une::string::suffix_array(empty).empty());\n\
    \    assert(m1une::string::lcp_array(empty, std::vector<int>()).empty());\n  \
    \  assert(m1une::string::lyndon_factor_boundaries(empty) == std::vector<int>(1,\
    \ 0));\n    assert(m1une::string::lyndon_factorization(empty).empty());\n    assert(m1une::string::minimum_cyclic_shift(empty)\
    \ == 0);\n\n    auto empty_palindromes = m1une::string::manacher(empty);\n   \
    \ assert(empty_palindromes.empty());\n    assert(empty_palindromes.longest_length()\
    \ == 0);\n    assert(empty_palindromes.is_palindrome(0, 0));\n\n    std::string\
    \ text = \"aaaa\";\n    assert(\n        m1une::string::kmp_search(text, std::string(\"\
    aa\")) ==\n        std::vector<int>({0, 1, 2})\n    );\n    assert(\n        m1une::string::kmp_search(text,\
    \ empty) ==\n        std::vector<int>({0, 1, 2, 3, 4})\n    );\n\n    std::vector<int>\
    \ values;\n    values.push_back(2);\n    values.push_back(-1);\n    values.push_back(2);\n\
    \    assert(\n        m1une::string::suffix_array(values) ==\n        std::vector<int>({1,\
    \ 2, 0})\n    );\n    assert(\n        m1une::string::z_algorithm(values) ==\n\
    \        std::vector<int>({3, 0, 1})\n    );\n    assert(\n        m1une::string::lyndon_factor_boundaries(values)\
    \ ==\n        std::vector<int>({0, 1, 3})\n    );\n    assert(m1une::string::minimum_cyclic_shift(values)\
    \ == 1);\n\n    std::string bytes;\n    bytes.push_back(char(255));\n    bytes.push_back(char(0));\n\
    \    bytes.push_back(char(128));\n    assert(\n        m1une::string::suffix_array(bytes)\
    \ ==\n        std::vector<int>({1, 2, 0})\n    );\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 31;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 1500; trial++) {\n        int n = int(random()\
    \ % 45);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 4);\n\n        std::vector<int> z = m1une::string::z_algorithm(text);\n\
    \        for (int i = 0; i < n; i++) {\n            [[maybe_unused]] int expected\
    \ = 0;\n            while (\n                i + expected < n &&\n           \
    \     text[expected] == text[i + expected]\n            ) {\n                expected++;\n\
    \            }\n            assert(z[i] == expected);\n        }\n\n        std::vector<int>\
    \ prefix = m1une::string::prefix_function(text);\n        for (int i = 0; i <\
    \ n; i++) {\n            [[maybe_unused]] int expected = 0;\n            for (int\
    \ length = 1; length <= i; length++) {\n                if (\n               \
    \     text.substr(0, length) ==\n                    text.substr(i - length +\
    \ 1, length)\n                ) {\n                    expected = length;\n  \
    \              }\n            }\n            assert(prefix[i] == expected);\n\
    \        }\n\n        int pattern_length = int(random() % 12);\n        std::string\
    \ pattern(pattern_length, 'a');\n        for (char& character : pattern) character\
    \ = char('a' + random() % 4);\n        std::vector<int> expected_occurrences;\n\
    \        for (int i = 0; i + pattern_length <= n; i++) {\n            if (text.substr(i,\
    \ pattern_length) == pattern) {\n                expected_occurrences.push_back(i);\n\
    \            }\n        }\n        assert(\n            m1une::string::kmp_search(text,\
    \ pattern) ==\n            expected_occurrences\n        );\n\n        m1une::string::ManacherResult\
    \ palindromes =\n            m1une::string::manacher(text);\n        int longest\
    \ = 0;\n        for (int left = 0; left <= n; left++) {\n            for (int\
    \ right = left; right <= n; right++) {\n                bool expected = true;\n\
    \                for (int offset = 0; offset < (right - left) / 2; offset++) {\n\
    \                    if (text[left + offset] != text[right - 1 - offset]) {\n\
    \                        expected = false;\n                        break;\n \
    \                   }\n                }\n                assert(palindromes.is_palindrome(left,\
    \ right) == expected);\n                if (expected) longest = std::max(longest,\
    \ right - left);\n            }\n        }\n        assert(palindromes.longest_length()\
    \ == longest);\n\n        std::vector<int> suffixes = m1une::string::suffix_array(text);\n\
    \        std::vector<int> expected_suffixes(n);\n        std::iota(expected_suffixes.begin(),\
    \ expected_suffixes.end(), 0);\n        std::sort(\n            expected_suffixes.begin(),\n\
    \            expected_suffixes.end(),\n            [&text](int a, int b) {\n \
    \               return text.substr(a) < text.substr(b);\n            }\n     \
    \   );\n        assert(suffixes == expected_suffixes);\n\n        std::vector<int>\
    \ lcp = m1une::string::lcp_array(text, suffixes);\n        for (int i = 0; i +\
    \ 1 < n; i++) {\n            int expected = 0;\n            while (\n        \
    \        suffixes[i] + expected < n &&\n                suffixes[i + 1] + expected\
    \ < n &&\n                text[suffixes[i] + expected] ==\n                  \
    \  text[suffixes[i + 1] + expected]\n            ) {\n                expected++;\n\
    \            }\n            assert(lcp[i] == expected);\n        }\n\n       \
    \ std::vector<std::pair<int, int>> lyndon_factors =\n            m1une::string::lyndon_factorization(text);\n\
    \        int minimum_shift = m1une::string::minimum_cyclic_shift(text);\n    \
    \    assert(\n            (n == 0 && minimum_shift == 0) ||\n            (0 <=\
    \ minimum_shift && minimum_shift < n)\n        );\n        std::string restored;\n\
    \        std::vector<std::string> factor_words;\n        for (auto [left, right]\
    \ : lyndon_factors) {\n            assert(0 <= left && left < right && right <=\
    \ n);\n            std::string word = text.substr(left, right - left);\n     \
    \       restored += word;\n            factor_words.push_back(word);\n       \
    \ }\n        assert(restored == text);\n        for (int i = 0; i + 1 < int(factor_words.size());\
    \ i++) {\n            assert(!(factor_words[i] < factor_words[i + 1]));\n    \
    \    }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_edge_cases();\n\
    \    test_randomized();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  dependsOn:
  - string/all.hpp
  - string/aho_corasick.hpp
  - string/eertree.hpp
  - string/levenshtein_distance.hpp
  - string/longest_common_extension.hpp
  - string/suffix_array.hpp
  - string/longest_common_subsequence.hpp
  - string/longest_common_substring.hpp
  - string/lyndon_factorization.hpp
  - string/manacher.hpp
  - string/prefix_function.hpp
  - string/rolling_hash.hpp
  - string/runs.hpp
  - string/string_hash.hpp
  - string/suffix_automaton.hpp
  - string/trie.hpp
  - string/wildcard_pattern_matching.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - string/z_algorithm.hpp
  isVerificationFile: true
  path: verify/string/string_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 04:21:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/string_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/string/string_algorithms.test.cpp
- /verify/verify/string/string_algorithms.test.cpp.html
title: verify/string/string_algorithms.test.cpp
---
