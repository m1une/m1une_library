---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy:
  - icon: ':x:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  - icon: ':x:'
    path: verify/string/wildcard_pattern_matching.test.cpp
    title: verify/string/wildcard_pattern_matching.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_STRING_WILDCARD_PATTERN_MATCHING_HPP\n#define M1UNE_STRING_WILDCARD_PATTERN_MATCHING_HPP\
    \ 1\n\n#include <array>\n#include <string>\n#include <vector>\n\n#include \"../math/fps/convolution.hpp\"\
    \n\nnamespace m1une {\nnamespace string {\n\nnamespace internal {\n\ntemplate\
    \ <class Mint>\nstd::vector<Mint> wildcard_mismatch_scores(\n    const std::string&\
    \ text,\n    const std::string& pattern,\n    char wildcard\n) {\n    int n =\
    \ int(text.size());\n    int m = int(pattern.size());\n    std::array<std::vector<Mint>,\
    \ 3> text_powers;\n    std::array<std::vector<Mint>, 3> pattern_powers;\n    for\
    \ (auto& powers : text_powers) powers.resize(n);\n    for (auto& powers : pattern_powers)\
    \ powers.resize(m);\n\n    auto encode = [wildcard](char character) {\n      \
    \  if (character == wildcard) return 0;\n        return int(static_cast<unsigned\
    \ char>(character)) + 1;\n    };\n    for (int i = 0; i < n; i++) {\n        Mint\
    \ value = encode(text[i]);\n        text_powers[0][i] = value;\n        text_powers[1][i]\
    \ = value * value;\n        text_powers[2][i] = value * value * value;\n    }\n\
    \    for (int i = 0; i < m; i++) {\n        Mint value = encode(pattern[m - 1\
    \ - i]);\n        pattern_powers[0][i] = value;\n        pattern_powers[1][i]\
    \ = value * value;\n        pattern_powers[2][i] = value * value * value;\n  \
    \  }\n\n    std::vector<Mint> scores(n - m + 1);\n    for (int power = 0; power\
    \ < 3; power++) {\n        std::vector<Mint> product = fps::convolution(\n   \
    \         text_powers[power],\n            pattern_powers[2 - power]\n       \
    \ );\n        Mint multiplier = power == 1 ? Mint(-2) : Mint(1);\n        for\
    \ (int start = 0; start <= n - m; start++) {\n            scores[start] += multiplier\
    \ * product[start + m - 1];\n        }\n    }\n    return scores;\n}\n\n}  //\
    \ namespace internal\n\n// result[i] is true exactly when pattern matches text[i,\
    \ i + pattern.size()).\n// The wildcard character matches every character on either\
    \ side.\ninline std::vector<bool> wildcard_pattern_matching(\n    const std::string&\
    \ text,\n    const std::string& pattern,\n    char wildcard = '*'\n) {\n    int\
    \ n = int(text.size());\n    int m = int(pattern.size());\n    if (m == 0) return\
    \ std::vector<bool>(n + 1, true);\n    if (n < m) return {};\n\n    using Mint1\
    \ = math::ModInt<469762049>;\n    using Mint2 = math::ModInt<754974721>;\n   \
    \ std::vector<Mint1> first_scores =\n        internal::wildcard_mismatch_scores<Mint1>(text,\
    \ pattern, wildcard);\n    std::vector<Mint2> second_scores =\n        internal::wildcard_mismatch_scores<Mint2>(text,\
    \ pattern, wildcard);\n\n    std::vector<bool> result(n - m + 1, false);\n   \
    \ for (int start = 0; start <= n - m; start++) {\n        result[start] = first_scores[start].val()\
    \ == 0 &&\n                        second_scores[start].val() == 0;\n    }\n \
    \   return result;\n}\n\n}  // namespace string\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_STRING_WILDCARD_PATTERN_MATCHING_HPP\n"
  dependsOn:
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: string/wildcard_pattern_matching.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-13 23:10:39+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/wildcard_pattern_matching.test.cpp
documentation_of: string/wildcard_pattern_matching.hpp
layout: document
title: Wildcard Pattern Matching
---

## Overview

Wildcard pattern matching checks every alignment of a pattern within a text.
By default, `*` matches any character, whether it occurs in the text or the
pattern. A different wildcard byte can be selected explicitly.

The implementation uses exact NTT convolutions rather than randomized hashing.

## Function

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<bool> wildcard_pattern_matching(const string& text, const string& pattern, char wildcard = '*')` | Returns one flag for each alignment; result `i` describes `text[i, i + pattern.size())`. | $O((N + M) \log(N + M))$ time and $O(N + M)$ memory |

An empty pattern matches at all `N + 1` positions. If the pattern is longer
than the text, the result is empty. Characters are treated as bytes, so this
function does not perform Unicode decoding.

## Example

```cpp
#include "string/wildcard_pattern_matching.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "abacaba";
    std::string pattern = "a*a";
    std::vector<bool> matches =
        m1une::string::wildcard_pattern_matching(text, pattern);

    for (int i = 0; i < int(matches.size()); i++) {
        if (matches[i]) std::cout << i << '\n';
    }
}
```
